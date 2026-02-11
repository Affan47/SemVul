GeoIP_id_by_name_gl(GeoIP * gi, const char *name, GeoIPLookup *gl )
{
    unsigned long ipnum;
    int ret;
    if (name == NULL) {
        return 0;
    }
    if (gi->databaseType != GEOIP_LARGE_COUNTRY_EDITION && gi->databaseType !=
        GEOIP_COUNTRY_EDITION && gi->databaseType != GEOIP_PROXY_EDITION &&
        gi->databaseType != GEOIP_NETSPEED_EDITION) {
        printf("Invalid database type %s, expected %s\n",
               get_db_description(gi->databaseType),
               get_db_description(GEOIP_COUNTRY_EDITION));
        return 0;
    }
    if (!(ipnum = _GeoIP_lookupaddress(name))) {
        return 0;
    }
    ret = _GeoIP_seek_record_gl(gi, ipnum, gl) - gi->databaseSegments[0];
    return ret;
}
