col_create_path_data(struct path_data **name_path,
                                const char *name, int length,
                                const char *property, int property_len,
                                char sep)
{
    int error = EOK;
    struct path_data *new_name_path;

    TRACE_FLOW_STRING("col_create_path_data", "Entry.");

    TRACE_INFO_STRING("Constructing path from name:", name);
    TRACE_INFO_STRING("Constructing path from property:", property);


    new_name_path = (struct path_data *)malloc(sizeof(struct path_data));
    if (new_name_path == NULL) {
        TRACE_ERROR_NUMBER("Failed to allocate memory for new path struct.", ENOMEM);
        return ENOMEM;
    }
    new_name_path->name = malloc(length + property_len + 2);
    if (new_name_path->name == NULL) {
        TRACE_ERROR_NUMBER("Failed to allocate memory for new path name.", ENOMEM);
        free(new_name_path);
        return ENOMEM;
    }


    new_name_path->length = 0;

    if(length > 0) {
        memcpy(new_name_path->name, name, length);
        new_name_path->length = length;
        new_name_path->name[new_name_path->length] = sep;
        new_name_path->length++;
        new_name_path->name[new_name_path->length] = '\0';
        TRACE_INFO_STRING("Name so far:", new_name_path->name);
        TRACE_INFO_NUMBER("Len so far:", new_name_path->length);
    }
    memcpy(&new_name_path->name[new_name_path->length], property, property_len);
    new_name_path->length += property_len;
    new_name_path->name[new_name_path->length] = '\0';


    new_name_path->previous_path = *name_path;
    *name_path = new_name_path;

    TRACE_INFO_STRING("Constructed path", new_name_path->name);


    TRACE_FLOW_NUMBER("col_create_path_data. Returning:", error);
    return error;
}
