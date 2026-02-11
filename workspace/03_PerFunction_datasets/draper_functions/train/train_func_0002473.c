iconv_iconv(int argc, VALUE *argv, VALUE self)
{
    VALUE str, n1, n2;
    VALUE cd = check_iconv(self);
    long start = 0, length = 0, slen = 0;

    rb_scan_args(argc, argv, "12", &str, &n1, &n2);
    if (!NIL_P(str)) {
	VALUE n = rb_str_length(StringValue(str));
	slen = NUM2LONG(n);
    }
    if (argc != 2 || !RTEST(rb_range_beg_len(n1, &start, &length, slen, 0))) {
	if (NIL_P(n1) || ((start = NUM2LONG(n1)) < 0 ? (start += slen) >= 0 : start < slen)) {
	    length = NIL_P(n2) ? -1 : NUM2LONG(n2);
	}
    }
    if (start > 0 || length > 0) {
	rb_encoding *enc = rb_enc_get(str);
	const char *s = RSTRING_PTR(str), *e = s + RSTRING_LEN(str);
	const char *ps = s;
	if (start > 0) {
	    start = (ps = rb_enc_nth(s, e, start, enc)) - s;
	}
	if (length > 0) {
	    length = rb_enc_nth(ps, e, length, enc) - ps;
	}
    }

    return iconv_convert(VALUE2ICONV(cd), str, start, length, ENCODING_GET(self), NULL);
}
