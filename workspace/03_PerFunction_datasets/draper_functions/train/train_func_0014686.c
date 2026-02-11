iconv_init_state(VALUE self)
{
    iconv_t cd = VALUE2ICONV((VALUE)DATA_PTR(self));
    DATA_PTR(self) = NULL;
    return iconv_convert(cd, Qnil, 0, 0, ENCODING_GET(self), NULL);
}
