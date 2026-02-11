col_push_binary_property(struct collection_item *stack,
                             const char *property,
                             void *binary_data,
                             int length)
{
    int error = EOK;

    TRACE_FLOW_STRING("col_push_binary_property", "Entry point.");


    if (stack == NULL) {
        TRACE_ERROR_STRING("Stack can't be NULL", "");
        return EINVAL;
    }


    if (!col_is_of_class(stack, COL_CLASS_STACK)) {
        TRACE_ERROR_STRING("Wrong class", "");
        return EINVAL;
    }

    error = col_add_binary_property(stack, NULL, property, binary_data, length);

    TRACE_FLOW_STRING("col_push_binary_property", "Exit.");
    return error;
}
