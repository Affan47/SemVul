pm_genpd_sync_poweroff(struct generic_pm_domain *genpd,
				   bool timed)
{
	struct gpd_link *link;

	if (genpd->status == GPD_STATE_POWER_OFF)
		return;

	if (genpd->suspended_count != genpd->device_count
	    || atomic_read(&genpd->sd_count) > 0)
		return;

	genpd_power_off(genpd, timed);

	genpd->status = GPD_STATE_POWER_OFF;

	list_for_each_entry(link, &genpd->slave_links, slave_node) {
		genpd_sd_counter_dec(link->master);
		pm_genpd_sync_poweroff(link->master, timed);
	}
}
