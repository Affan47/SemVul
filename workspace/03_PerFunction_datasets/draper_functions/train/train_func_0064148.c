plist_data_compare(gconstpointer a, gconstpointer b)
{
    plist_data_t val_a = NULL;
    plist_data_t val_b = NULL;

    if (!a || !b)
        return FALSE;

    if (!((GNode *) a)->data || !((GNode *) b)->data)
        return FALSE;

    val_a = plist_get_data((plist_t) a);
    val_b = plist_get_data((plist_t) b);

    if (val_a->type != val_b->type)
        return FALSE;

    switch (val_a->type)
    {
    case PLIST_BOOLEAN:
    case PLIST_UINT:
    case PLIST_REAL:
        if (val_a->intval == val_b->intval)
            return TRUE;
        else
            return FALSE;

    case PLIST_KEY:
    case PLIST_STRING:
        if (!strcmp(val_a->strval, val_b->strval))
            return TRUE;
        else
            return FALSE;

    case PLIST_DATA:
        if (!memcmp(val_a->buff, val_b->buff, val_a->length))
            return TRUE;
        else
            return FALSE;
    case PLIST_ARRAY:
    case PLIST_DICT:

        if (a == b)
            return TRUE;
        else
            return FALSE;
        break;
    case PLIST_DATE:
        if (!memcmp(&(val_a->timeval), &(val_b->timeval), sizeof(GTimeVal)))
            return TRUE;
        else
            return FALSE;
    default:
        break;
    }
    return FALSE;
}
