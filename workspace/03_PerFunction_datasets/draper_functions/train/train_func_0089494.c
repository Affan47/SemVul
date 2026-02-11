cddb_site_set_address(cddb_site_t *site,
                                   const char *address, unsigned int port)
{
    ASSERT_NOT_NULL(site);
    ASSERT_NOT_NULL(address);
    FREE_NOT_NULL(site->address);
    site->address = strdup(address);
    if (!site->address) {
        return CDDB_ERR_OUT_OF_MEMORY;
    }
    site->port = port;
    return CDDB_ERR_OK;
}
