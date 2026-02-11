default_power_down_ok(struct dev_pm_domain *pd)
{
	struct generic_pm_domain *genpd = pd_to_genpd(pd);
	struct gpd_link *link;
	struct pm_domain_data *pdd;
	s64 min_off_time_ns;
	s64 off_on_time_ns;

	if (genpd->max_off_time_changed) {
		struct gpd_link *link;


		list_for_each_entry(link, &genpd->slave_links, slave_node)
			link->master->max_off_time_changed = true;

		genpd->max_off_time_changed = false;
		genpd->cached_power_down_ok = false;
		genpd->max_off_time_ns = -1;
	} else {
		return genpd->cached_power_down_ok;
	}

	off_on_time_ns = genpd->power_off_latency_ns +
				genpd->power_on_latency_ns;

	min_off_time_ns = -1;


	list_for_each_entry(link, &genpd->master_links, master_node) {
		struct generic_pm_domain *sd = link->slave;
		s64 sd_max_off_ns = sd->max_off_time_ns;

		if (sd_max_off_ns < 0)
			continue;


		if (sd_max_off_ns <= off_on_time_ns)
			return false;

		if (min_off_time_ns > sd_max_off_ns || min_off_time_ns < 0)
			min_off_time_ns = sd_max_off_ns;
	}


	list_for_each_entry(pdd, &genpd->dev_list, list_node) {
		struct gpd_timing_data *td;
		s64 constraint_ns;


		td = &to_gpd_data(pdd)->td;
		constraint_ns = td->effective_constraint_ns;

		if (constraint_ns < 0) {
			constraint_ns = dev_pm_qos_read_value(pdd->dev);
			constraint_ns *= NSEC_PER_USEC;
		}
		if (constraint_ns == 0)
			continue;


		if (constraint_ns <= off_on_time_ns)
			return false;

		if (min_off_time_ns > constraint_ns || min_off_time_ns < 0)
			min_off_time_ns = constraint_ns;
	}

	genpd->cached_power_down_ok = true;


	if (min_off_time_ns < 0)
		return true;


	genpd->max_off_time_ns = min_off_time_ns - genpd->power_on_latency_ns;
	return true;
}
