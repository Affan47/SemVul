character_data_handler(void *user_data, const char *data, int len)
{
    CAMLparam0();
    CAMLlocal1(str);
    value *handlers = user_data;

    str = alloc_string(len);
    memcpy(String_val(str), data, len);
    callback(Field(*handlers, EXPAT_CHARACTER_DATA_HANDLER), str);

    CAMLreturn0;
}
