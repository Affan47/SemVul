wl12xx_mac_in_fuse(struct wl1271 *wl)
{
	bool supported = false;
	u8 major, minor;

	if (wl->chip.id == CHIP_ID_128X_PG20) {
		major = WL128X_PG_GET_MAJOR(wl->hw_pg_ver);
		minor = WL128X_PG_GET_MINOR(wl->hw_pg_ver);


		if (major > 2 || (major == 2 && minor >= 1))
			supported = true;
	} else {
		major = WL127X_PG_GET_MAJOR(wl->hw_pg_ver);
		minor = WL127X_PG_GET_MINOR(wl->hw_pg_ver);


		if (major == 3 && minor >= 1)
			supported = true;
	}

	wl1271_debug(DEBUG_PROBE,
		     "PG Ver major = %d minor = %d, MAC %s present",
		     major, minor, supported ? "is" : "is not");

	return supported;
}
