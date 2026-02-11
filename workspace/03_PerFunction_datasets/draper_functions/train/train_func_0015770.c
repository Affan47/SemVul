json_array_append_null(JSON_Array *array) {
    JSON_Value *value = json_value_init_null();
    if (value == NULL)
        return JSONFailure;
    if (json_array_append_value(array, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}
