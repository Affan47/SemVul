cddb_site_set_description(cddb_site_t *site, const char *desc)
{
    ASSERT_NOT_NULL(site);
    FREE_NOT_NULL(site->desc);
    if (desc) {
        site->desc = strdup(desc);
        if (!site->desc) {
            return CDDB_ERR_OUT_OF_MEMORY;
        }
    }
    return CDDB_ERR_OK;
}
