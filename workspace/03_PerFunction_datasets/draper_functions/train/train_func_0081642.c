col_copy_item_with_cb(struct collection_item *collection,
                                 const char *property,
                                 int type,
                                 const void *data,
                                 int length,
                                 col_copy_cb copy_cb,
                                 void *ext_data)
{
    struct collection_item *item = NULL;
    int skip = 0;
    int error = EOK;

    TRACE_FLOW_STRING("col_copy_item_with_cb", "Entry point.");


    error = col_allocate_item(&item, property, data, length, type);
    if (error) {
        TRACE_ERROR_NUMBER("Failed to allocate item", error);
        return error;
    }


    if (copy_cb) {
        TRACE_INFO_STRING("Calling callback for item:", item->property);
        error = copy_cb(item, ext_data, &skip);
        if (error) {
            TRACE_ERROR_NUMBER("Callback failed", error);
            col_delete_item(item);
            return error;
        }
    }


    if (skip) col_delete_item(item);
    else {

        error = col_insert_item(collection,
                                NULL,
                                item,
                                COL_DSP_END,
                                NULL,
                                0,
                                0);
        if (error) {
            TRACE_ERROR_NUMBER("Failed to insert item", error);
            col_delete_item(item);
            return error;
        }
    }

    TRACE_FLOW_STRING("col_copy_item_with_cb", "Exit");
    return EOK;
}
