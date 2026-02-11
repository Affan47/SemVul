GeoIP_record_by_addr(GeoIP * gi, const char *addr)
{
    unsigned long ipnum;
    GeoIPLookup gl;
    if (addr == NULL) {
        return 0;
    }
    ipnum = GeoIP_addr_to_num(addr);
    return _get_record_gl(gi, ipnum, &gl);
}
