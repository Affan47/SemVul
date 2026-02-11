col_extract_item(struct collection_item *collection,
                     const char *subcollection,
                     int disposition,
                     const char *refprop,
                     int idx,
                     int type,
                     struct collection_item **ret_ref)
{
    struct collection_item *col = NULL;
    int error = EOK;

    TRACE_FLOW_STRING("col_extract_item", "Entry point");


    if ((collection == NULL) || (collection->type != COL_TYPE_COLLECTION)) {
        TRACE_ERROR_STRING("Collection can't be NULL", "");
        return EINVAL;
    }


    if (subcollection == NULL) {
        col = collection;
    }
    else {
        TRACE_INFO_STRING("Subcollection id not null, searching", subcollection);
        error = col_find_item_and_do(collection, subcollection,
                                     COL_TYPE_COLLECTIONREF,
                                     COL_TRAVERSE_DEFAULT,
                                     col_get_subcollection, (void *)(&col),
                                     COLLECTION_ACTION_FIND);
        if (error) {
            TRACE_ERROR_NUMBER("Search for subcollection returned error:", error);
            return error;
        }

        if (col == NULL) {
            TRACE_ERROR_STRING("Search for subcollection returned NULL pointer", "");
            return ENOENT;
        }

    }


    error = col_extract_item_from_current(col,
                                          disposition,
                                          refprop,
                                          idx,
                                          type,
                                          ret_ref);
    if (error) {
        TRACE_ERROR_NUMBER("Failed to extract item from the current collection", error);
        return error;
    }

    TRACE_FLOW_STRING("col_extract_item", "Exit");
    return EOK;
}
