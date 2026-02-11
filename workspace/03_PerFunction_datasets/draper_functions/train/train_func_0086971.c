col_collection_to_list(struct collection_item *handle, int *size, int *error)
{
    struct collection_iterator *iterator;
    struct collection_item *item = NULL;
    char **list;
    unsigned count;
    int err;
    int current = 0;

    TRACE_FLOW_STRING("col_collection_to_list","Entry");


    err = col_get_collection_count(handle, &count);
    if (err) {
        TRACE_ERROR_NUMBER("Failed to get count of items from collection.", err);
        if (error) *error = err;
        return NULL;
    }


    list = (char **)malloc(count * sizeof(char *));
    if (list == NULL) {
        TRACE_ERROR_NUMBER("Failed to get allocate memory.", ENOMEM);
        if (error) *error = ENOMEM;
        return NULL;
    }


    err =  col_bind_iterator(&iterator, handle, COL_TRAVERSE_ONELEVEL);
    if (err) {
        TRACE_ERROR_NUMBER("Failed to bind.", err);
        if (error) *error = err;
        free(list);
        return NULL;
    }

    while(1) {

        err = col_iterate_collection(iterator, &item);
        if (err) {
            TRACE_ERROR_NUMBER("Failed to iterate collection", err);
            if (error) *error = err;
            col_free_property_list(list);
            col_unbind_iterator(iterator);
            return NULL;
        }


        if (item == NULL) break;

        TRACE_INFO_STRING("Property:", col_get_item_property(item, NULL));


        if(col_get_item_type(item) == COL_TYPE_COLLECTION) continue;


        list[current] = strdup(col_get_item_property(item, NULL));
        if (list[current] == NULL) {
            TRACE_ERROR_NUMBER("Failed to dup string.", ENOMEM);
            if (error) *error = ENOMEM;
            col_free_property_list(list);
            return NULL;
        }
        current++;
    }

    list[current] = NULL;


    col_unbind_iterator(iterator);

    if (size) *size = (int)(count - 1);
    if (error) *error = EOK;

    TRACE_FLOW_STRING("col_collection_to_list returning", ((list == NULL) ? "NULL" : list[0]));
    return list;
}
