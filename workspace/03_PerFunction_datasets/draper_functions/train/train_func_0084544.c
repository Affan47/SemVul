of_add_property(struct device_node *np, struct property *prop)
{
	unsigned long flags;
	int rc;

	mutex_lock(&of_mutex);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	rc = __of_add_property(np, prop);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	if (!rc)
		__of_add_property_sysfs(np, prop);

	mutex_unlock(&of_mutex);

	if (!rc)
		of_property_notify(OF_RECONFIG_ADD_PROPERTY, np, prop, NULL);

	return rc;
}
