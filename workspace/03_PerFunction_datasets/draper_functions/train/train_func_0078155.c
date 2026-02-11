json_value_init_boolean(int boolean) {
    JSON_Value *new_value = (JSON_Value*)PARSON_MALLOC(sizeof(JSON_Value));
    if (!new_value)
        return NULL;
    new_value->type = JSONBoolean;
    new_value->value.boolean = boolean ? 1 : 0;
    return new_value;
}
