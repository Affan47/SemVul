opal_util_keyval_parse_init(void)
{
    OBJ_CONSTRUCT(&keyval_mutex, opal_mutex_t);

    return OPAL_SUCCESS;
}
