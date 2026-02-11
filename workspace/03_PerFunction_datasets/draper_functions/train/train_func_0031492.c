col_print_collection2(struct collection_item *handle)
{
    struct collection_iterator *iterator = NULL;
    int error = EOK;
    struct collection_item *item = NULL;
    int nest_level = 0;
    int dummy = 0;
    int line = 1;

    TRACE_FLOW_STRING("col_print_collection2", "Entry");


    if (handle == NULL) {
        TRACE_ERROR_STRING("No error list", "");
        return EINVAL;
    }


    error = col_bind_iterator(&iterator, handle,
                              COL_TRAVERSE_DEFAULT |
                              COL_TRAVERSE_END |
                              COL_TRAVERSE_SHOWSUB);
    if (error) {
        TRACE_ERROR_NUMBER("Error (bind):", error);
        return error;
    }

    do {

        error = col_iterate_collection(iterator, &item);
        if (error) {
            TRACE_ERROR_NUMBER("Error (iterate):", error);
            col_unbind_iterator(iterator);
            return error;
        }


        if (item == NULL) break;

        if (item->type != COL_TYPE_END) printf("%05d", line);

        col_debug_handle(item->property,
                         item->property_len,
                         item->type,
                         item->data,
                         item->length,
                         (void *)(&nest_level),
                         &dummy);
        line++;
    }
    while(1);


    col_unbind_iterator(iterator);

    TRACE_INFO_STRING("col_print_collection2", "Exit");
    return EOK;
}
