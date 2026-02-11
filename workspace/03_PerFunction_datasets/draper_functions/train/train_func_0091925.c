appStatsTruthValue_map(u_long * mib_appStatsTruthValue_val_ptr,
                       u_long raw_appStatsTruthValue_val)
{
    netsnmp_assert(NULL != mib_appStatsTruthValue_val_ptr);

    DEBUGMSGTL(("verbose:dessertAppStatsTable:appStatsTruthValue_map",
                "called\n"));


    switch (raw_appStatsTruthValue_val) {
    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSTRUTHVALUE_TRUE:
        *mib_appStatsTruthValue_val_ptr = TRUTHVALUE_TRUE;
        break;

    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSTRUTHVALUE_FALSE:
        *mib_appStatsTruthValue_val_ptr = TRUTHVALUE_FALSE;
        break;

    default:
        snmp_log(LOG_ERR,
                 "couldn't map value %ld for appStatsTruthValue\n",
                 raw_appStatsTruthValue_val);
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
}
