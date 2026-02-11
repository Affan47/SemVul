json_array_replace_value(JSON_Array *array, size_t ix, JSON_Value *value) {
    if (array == NULL || value == NULL || ix >= json_array_get_count(array)) {
        return JSONFailure;
    }
    json_value_free(json_array_get_value(array, ix));
    array->items[ix] = value;
    return JSONSuccess;
}
