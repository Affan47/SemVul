technology_disable(struct connman_technology *technology)
{
	int err;

	DBG("technology %p disable", technology);

	__sync_synchronize();
	if (technology->enabled == FALSE)
		return -EALREADY;

	if (technology->pending_reply != NULL)
		return -EBUSY;

	if (technology->tethering == TRUE)
		set_tethering(technology, FALSE);

	err = technology_affect_devices(technology, FALSE);

	if (technology->rfkill_driven == TRUE)
		err = __connman_rfkill_block(technology->type, TRUE);

	return err;
}
