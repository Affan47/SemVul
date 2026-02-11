col_insert_property_with_ref(struct collection_item *collection,
                                 const char *subcollection,
                                 int disposition,
                                 const char *refprop,
                                 int idx,
                                 unsigned flags,
                                 const char *property,
                                 int type,
                                 const void *data,
                                 int length,
                                 struct collection_item **ret_ref)
{
    int error;

    TRACE_FLOW_STRING("col_insert_property_with_ref", "Entry point.");


    if (collection == NULL) {
        TRACE_ERROR_STRING("Collection cant be NULL", "");
        return EINVAL;
    }

    error = col_insert_property_with_ref_int(collection,
                                             subcollection,
                                             disposition,
                                             refprop,
                                             idx,
                                             flags,
                                             property,
                                             type,
                                             data,
                                             length,
                                             ret_ref);

    TRACE_FLOW_NUMBER("col_insert_property_with_ref_int Returning:", error);
    return error;
}
