netsnmp_ds_get_boolean(int storeid, int which)
{
    if (storeid < 0 || storeid >= NETSNMP_DS_MAX_IDS ||
	which   < 0 || which   >= NETSNMP_DS_MAX_SUBIDS) {
        return SNMPERR_GENERR;
    }

    return (netsnmp_ds_booleans[storeid][which/8] & (1 << (which % 8))) ? 1:0;
}
