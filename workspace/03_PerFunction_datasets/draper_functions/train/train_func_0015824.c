hash_lookup(hash_table_t *table, hash_key_t *key, hash_value_t *value)
{
    segment_t element, *chain;

    if (!table) return HASH_ERROR_BAD_TABLE;

    if (!is_valid_key_type(key->type))
        return HASH_ERROR_BAD_KEY_TYPE;

    lookup(table, key, &element, &chain);

    if (element) {
        *value = element->entry.value;
        return HASH_SUCCESS;
    } else {
        return HASH_ERROR_KEY_NOT_FOUND;
    }
}
