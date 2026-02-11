init(void)
{
    OBJ_CONSTRUCT(&hash_data, opal_hash_table_t);
    opal_hash_table_init(&hash_data, 256);
    return OPAL_SUCCESS;
}
