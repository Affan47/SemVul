iconv_conv(int argc, VALUE *argv, VALUE self)
{
    iconv_t cd = VALUE2ICONV(check_iconv(self));
    VALUE str, s;
    int toidx = ENCODING_GET(self);

    str = iconv_convert(cd, Qnil, 0, 0, toidx, NULL);
    if (argc > 0) {
	do {
	    s = iconv_convert(cd, *argv++, 0, -1, toidx, NULL);
	    if (RSTRING_LEN(s))
		rb_str_buf_append(str, s);
	} while (--argc);
	s = iconv_convert(cd, Qnil, 0, 0, toidx, NULL);
	if (RSTRING_LEN(s))
	    rb_str_buf_append(str, s);
    }

    return str;
}
