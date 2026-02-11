GeoIP_name_by_addr_v6_gl(GeoIP * gi, const char *addr, GeoIPLookup * gl)
{
    geoipv6_t ipnum;
    if (addr == NULL) {
        return NULL;
    }
    ipnum = _GeoIP_addr_to_num_v6(addr);
    return _get_name_v6_gl(gi, ipnum, gl);
}
