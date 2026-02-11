netsnmp_ds_set_void(int storeid, int which, void *value)
{
    if (storeid < 0 || storeid >= NETSNMP_DS_MAX_IDS ||
	which   < 0 || which   >= NETSNMP_DS_MAX_SUBIDS) {
        return SNMPERR_GENERR;
    }

    DEBUGMSGTL(("netsnmp_ds_set_void", "Setting %s:%d = %p\n",
                stores[storeid], which, value));

    netsnmp_ds_voids[storeid][which] = value;

    return SNMPERR_SUCCESS;
}
