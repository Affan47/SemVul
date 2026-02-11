json_object_get(const json_t *json, const char *key)
{
    json_object_t *object;

    if(!key || !json_is_object(json))
        return NULL;

    object = json_to_object(json);
    return hashtable_get(&object->hashtable, key);
}
