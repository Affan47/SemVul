drivers_heartbeat(int state)
{
	Driver *drv;

	debug(RPT_DEBUG, "%s(state=%d)", __FUNCTION__, state);

	ForAllDrivers(drv) {
		if (drv->heartbeat)
			drv->heartbeat(drv, state);
		else
			driver_alt_heartbeat(drv, state);
	}
}
