col_simple_traverse_handler(struct collection_item *head,
                                       struct collection_item *previous,
                                       struct collection_item *current,
                                       void *traverse_data,
                                       col_item_fn user_item_handler,
                                       void *custom_data,
                                       int *stop)
{
    int error = EOK;
    struct collection_item end_item;
    char zero = '\0';

    TRACE_FLOW_STRING("col_simple_traverse_handler", "Entry.");

    if (current == NULL) {
        memset((void *)&end_item, 0, sizeof(struct collection_item));
        end_item.type = COL_TYPE_END;
        end_item.property = &zero;
        current = &end_item;
    }

    error = user_item_handler(current->property,
                              current->property_len,
                              current->type,
                              current->data,
                              current->length,
                              custom_data,
                              stop);

    TRACE_FLOW_NUMBER("col_simple_traverse_handler. Returning:", error);
    return error;
}
