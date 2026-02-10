json_array_deep_copy(json_t *array)
{
    json_t *result;
    unsigned int i;

    result = json_array();
    if(!result)
        return NULL;

    for(i = 0; i < json_array_size(array); i++)
        json_array_append_new(result, json_deep_copy(json_array_get(array, i)));

    return result;
}
