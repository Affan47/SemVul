__of_add_property_sysfs(struct device_node *np, struct property *pp)
{
	int rc;


	bool secure = strncmp(pp->name, "security-", 9) == 0;

	if (!IS_ENABLED(CONFIG_SYSFS))
		return 0;

	if (!of_kset || !of_node_is_attached(np))
		return 0;

	sysfs_bin_attr_init(&pp->attr);
	pp->attr.attr.name = safe_name(&np->kobj, pp->name);
	pp->attr.attr.mode = secure ? S_IRUSR : S_IRUGO;
	pp->attr.size = secure ? 0 : pp->length;
	pp->attr.read = of_node_property_read;

	rc = sysfs_create_bin_file(&np->kobj, &pp->attr);
	WARN(rc, "error adding attribute %s to node %s\n", pp->name, np->full_name);
	return rc;
}
