__power_supply_register(struct device *parent,
				   const struct power_supply_desc *desc,
				   const struct power_supply_config *cfg,
				   bool ws)
{
	struct device *dev;
	struct power_supply *psy;
	int rc;

	if (!parent)
		pr_warn("%s: Expected proper parent device for '%s'\n",
			__func__, desc->name);

	psy = kzalloc(sizeof(*psy), GFP_KERNEL);
	if (!psy)
		return ERR_PTR(-ENOMEM);

	dev = &psy->dev;

	device_initialize(dev);

	dev->class = power_supply_class;
	dev->type = &power_supply_dev_type;
	dev->parent = parent;
	dev->release = power_supply_dev_release;
	dev_set_drvdata(dev, psy);
	psy->desc = desc;
	if (cfg) {
		psy->drv_data = cfg->drv_data;
		psy->of_node = cfg->of_node;
		psy->supplied_to = cfg->supplied_to;
		psy->num_supplicants = cfg->num_supplicants;
	}

	rc = dev_set_name(dev, "%s", desc->name);
	if (rc)
		goto dev_set_name_failed;

	INIT_WORK(&psy->changed_work, power_supply_changed_work);
	INIT_DELAYED_WORK(&psy->deferred_register_work,
			  power_supply_deferred_register_work);

	rc = power_supply_check_supplies(psy);
	if (rc) {
		dev_info(dev, "Not all required supplies found, defer probe\n");
		goto check_supplies_failed;
	}

	spin_lock_init(&psy->changed_lock);
	rc = device_init_wakeup(dev, ws);
	if (rc)
		goto wakeup_init_failed;

	rc = device_add(dev);
	if (rc)
		goto device_add_failed;

	rc = psy_register_thermal(psy);
	if (rc)
		goto register_thermal_failed;

	rc = psy_register_cooler(psy);
	if (rc)
		goto register_cooler_failed;

	rc = power_supply_create_triggers(psy);
	if (rc)
		goto create_triggers_failed;


	atomic_inc(&psy->use_cnt);

	queue_delayed_work(system_power_efficient_wq,
			   &psy->deferred_register_work,
			   POWER_SUPPLY_DEFERRED_REGISTER_TIME);

	return psy;

create_triggers_failed:
	psy_unregister_cooler(psy);
register_cooler_failed:
	psy_unregister_thermal(psy);
register_thermal_failed:
	device_del(dev);
device_add_failed:
wakeup_init_failed:
check_supplies_failed:
dev_set_name_failed:
	put_device(dev);
	return ERR_PTR(rc);
}
