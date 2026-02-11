GeoIP_region_by_ipnum_gl(GeoIP * gi, unsigned long ipnum,
                                       GeoIPLookup * gl)
{
    if (gi->databaseType != GEOIP_REGION_EDITION_REV0 &&
        gi->databaseType != GEOIP_REGION_EDITION_REV1) {
        printf("Invalid database type %s, expected %s\n",
               get_db_description(gi->databaseType),
               get_db_description(GEOIP_REGION_EDITION_REV1));
        return NULL;
    }
    return _get_region_gl(gi, ipnum, gl);
}
