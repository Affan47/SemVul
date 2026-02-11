release_zone(struct powercap_zone *power_zone)
{
	struct rapl_domain *rd = power_zone_to_rapl_domain(power_zone);
	struct rapl_package *rp;


	if (rd->id == RAPL_DOMAIN_PACKAGE) {
		rp = find_package_by_id(rd->package_id);
		if (!rp) {
			dev_warn(&power_zone->dev, "no package id %s\n",
				rd->name);
			return -ENODEV;
		}
		kfree(rd);
		rp->domains = NULL;
	}

	return 0;

}
