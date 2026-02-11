charger_extcon_work(struct work_struct *work)
{
	struct charger_cable *cable =
			container_of(work, struct charger_cable, wq);
	int ret;

	if (cable->attached && cable->min_uA != 0 && cable->max_uA != 0) {
		ret = regulator_set_current_limit(cable->charger->consumer,
					cable->min_uA, cable->max_uA);
		if (ret < 0) {
			pr_err("Cannot set current limit of %s (%s)\n",
			       cable->charger->regulator_name, cable->name);
			return;
		}

		pr_info("Set current limit of %s : %duA ~ %duA\n",
			cable->charger->regulator_name,
			cable->min_uA, cable->max_uA);
	}

	try_charger_enable(cable->cm, cable->attached);
}
