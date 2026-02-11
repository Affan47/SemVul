appStatsValueType_map(u_long * mib_appStatsValueType_val_ptr,
                      u_long raw_appStatsValueType_val)
{
    netsnmp_assert(NULL != mib_appStatsValueType_val_ptr);

    DEBUGMSGTL(("verbose:dessertAppStatsTable:appStatsValueType_map",
                "called\n"));


    switch (raw_appStatsValueType_val) {
    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSVALUETYPE_BOOL:
        *mib_appStatsValueType_val_ptr = APPSTATSVALUETYPE_BOOL;
        break;

    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSVALUETYPE_INT32:
        *mib_appStatsValueType_val_ptr = APPSTATSVALUETYPE_INT32;
        break;

    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSVALUETYPE_UINT32:
        *mib_appStatsValueType_val_ptr = APPSTATSVALUETYPE_UINT32;
        break;

    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSVALUETYPE_COUNTER64:
        *mib_appStatsValueType_val_ptr = APPSTATSVALUETYPE_COUNTER64;
        break;

    case INTERNAL_DESSERTAPPSTATSTABLE_APPSTATSVALUETYPE_OCTETSTRING:
        *mib_appStatsValueType_val_ptr = APPSTATSVALUETYPE_OCTETSTRING;
        break;

    default:
        snmp_log(LOG_ERR, "couldn't map value %ld for appStatsValueType\n",
                 raw_appStatsValueType_val);
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
}
