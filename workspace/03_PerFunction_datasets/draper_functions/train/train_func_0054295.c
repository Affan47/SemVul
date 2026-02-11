col_insert_str_property_with_ref(struct collection_item *ci,
                                     const char *subcollection,
                                     int disposition,
                                     const char *refprop,
                                     int idx,
                                     unsigned flags,
                                     const char *property,
                                     const char *string,
                                     int length,
                                     struct collection_item **ret_ref)
{
    int error = EOK;
    void *ptr;

    TRACE_FLOW_STRING("col_insert_string_property_with_ref", "Entry.");

    if (length == 0) length = strlen(string) + 1;


    memcpy(&ptr, &string, sizeof(void *));

    error = col_insert_property_with_ref(ci,
                                         subcollection,
                                         disposition,
                                         refprop,
                                         idx,
                                         flags,
                                         property,
                                         COL_TYPE_STRING,
                                         ptr,
                                         length,
                                         ret_ref);

    TRACE_FLOW_NUMBER("col_insert_string_property_with_ref returning", error);
    return error;
}
