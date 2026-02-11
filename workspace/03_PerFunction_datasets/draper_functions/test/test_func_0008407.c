kvp_value_compare(const KvpValue * kva, const KvpValue * kvb)
{
    if (kva == kvb) return 0;

    if (!kva && kvb) return -1;
    if (kva && !kvb) return 1;

    if (kva->type < kvb->type) return -1;
    if (kva->type > kvb->type) return 1;

    switch (kva->type)
    {
    case KVP_TYPE_GINT64:
        if (kva->value.int64 < kvb->value.int64) return -1;
        if (kva->value.int64 > kvb->value.int64) return 1;
        return 0;
        break;
    case KVP_TYPE_DOUBLE:
        return double_compare(kva->value.dbl, kvb->value.dbl);
        break;
    case KVP_TYPE_NUMERIC:
        return gnc_numeric_compare (kva->value.numeric, kvb->value.numeric);
        break;
    case KVP_TYPE_STRING:
        return strcmp(kva->value.str, kvb->value.str);
        break;
    case KVP_TYPE_GUID:
        return guid_compare(kva->value.guid, kvb->value.guid);
        break;
    case KVP_TYPE_TIMESPEC:
        return timespec_cmp(&(kva->value.timespec), &(kvb->value.timespec));
        break;
    case KVP_TYPE_GDATE:
        return g_date_compare(&(kva->value.gdate), &(kvb->value.gdate));
        break;
    case KVP_TYPE_BINARY:


        if (kva->value.binary.datasize < kvb->value.binary.datasize) return -1;
        if (kva->value.binary.datasize > kvb->value.binary.datasize) return 1;
        return memcmp(kva->value.binary.data,
                      kvb->value.binary.data,
                      kva->value.binary.datasize);
        break;
    case KVP_TYPE_GLIST:
        return kvp_glist_compare(kva->value.list, kvb->value.list);
        break;
    case KVP_TYPE_FRAME:
        return kvp_frame_compare(kva->value.frame, kvb->value.frame);
        break;
    }
    PERR ("reached unreachable code.");
    return FALSE;
}
