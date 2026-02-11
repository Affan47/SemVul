kvv_start(void)
{
    static int started = 0;
    int val;
    char *p;


    if (started)
	return;

    started = 1;


    if ((p = cfg_get(SECTION, "StationID", DEFAULT_STATION_ID)) != NULL) {
	station_id = malloc(strlen(p) + 1);
	strcpy(station_id, p);
    }
    info("[KVV] Using station %s", station_id);

    if ((p = cfg_get(SECTION, "Proxy", NULL)) != NULL) {
	proxy_name = malloc(strlen(p) + 1);
	strcpy(proxy_name, p);
	info("[KVV] Using proxy \"%s\"", proxy_name);
    }

    if (cfg_number(SECTION, "Port", 0, 0, 65535, &val) > 0) {
	port = val;
	info("[KVV] Using port %d", port);
    } else {
	info("[KVV] Using default port %d", port);
    }

    if (cfg_number(SECTION, "Refresh", 0, 0, 65535, &val) > 0) {
	refresh = val;
	info("[KVV] Using %d seconds refresh interval", refresh);
    } else {
	info("[KVV] Using default refresh interval of %d seconds", refresh);
    }

    if (cfg_number(SECTION, "Abbreviate", 0, 0, 65535, &val) > 0) {
	abbreviate = val;
	info("[KVV] Abbreviation enabled: %s", abbreviate ? "on" : "off");
    } else {
	info("[KVV] Default abbreviation setting: %s", abbreviate ? "on" : "off");
    }

}
