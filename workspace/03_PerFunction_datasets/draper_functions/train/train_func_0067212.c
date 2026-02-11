io_setstrbuf(VALUE *str,long len)
{
#ifdef _WIN32
    if (NIL_P(*str)) {
	*str = rb_str_new(0, len+1);
	rb_str_set_len(*str,len);
    }
    else {
	StringValue(*str);
	rb_str_modify(*str);
	rb_str_resize(*str, len+1);
	rb_str_set_len(*str,len);
    }
#else
    if (NIL_P(*str)) {
	*str = rb_str_new(0, len);
    }
    else {
	StringValue(*str);
	rb_str_modify(*str);
	rb_str_resize(*str, len);
    }
#endif
}
