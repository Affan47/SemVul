phy_find(struct device *dev, const char *con_id)
{
	const char *dev_id = dev_name(dev);
	struct phy_lookup *p, *pl = NULL;

	mutex_lock(&phy_provider_mutex);
	list_for_each_entry(p, &phys, node)
		if (!strcmp(p->dev_id, dev_id) && !strcmp(p->con_id, con_id)) {
			pl = p;
			break;
		}
	mutex_unlock(&phy_provider_mutex);

	return pl ? pl->phy : ERR_PTR(-ENODEV);
}
