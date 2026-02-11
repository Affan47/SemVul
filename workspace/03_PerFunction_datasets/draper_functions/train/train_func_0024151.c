ipSystemStatsHCInMcastOctets_get(ipSystemStatsTable_rowreq_ctx *
                                 rowreq_ctx,
                                 U64 *
                                 ipSystemStatsHCInMcastOctets_val_ptr)
{

    netsnmp_assert(NULL != ipSystemStatsHCInMcastOctets_val_ptr);


    if (!rowreq_ctx->data->stats.columnAvail[IPSYSTEMSTATSTABLE_HCINMCASTOCTETS])
        return MFD_SKIP;

    (*ipSystemStatsHCInMcastOctets_val_ptr).low =
        rowreq_ctx->data->stats.HCInMcastOctets.low;
    (*ipSystemStatsHCInMcastOctets_val_ptr).high =
        rowreq_ctx->data->stats.HCInMcastOctets.high;

    return MFD_SUCCESS;
}
