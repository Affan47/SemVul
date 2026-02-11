rb_str_times(str, times)
    VALUE str;
    VALUE times;
{
    VALUE str2;
    long i, len;

    len = NUM2LONG(times);
    if (len < 0) {
	rb_raise(rb_eArgError, "negative argument");
    }
    if (len && LONG_MAX/len <  RSTRING(str)->len) {
	rb_raise(rb_eArgError, "argument too big");
    }

    str2 = rb_str_new5(str,0, len *= RSTRING(str)->len);
    for (i = 0; i < len; i += RSTRING(str)->len) {
	memcpy(RSTRING(str2)->ptr + i,
	       RSTRING(str)->ptr, RSTRING(str)->len);
    }
    RSTRING(str2)->ptr[RSTRING(str2)->len] = '\0';

    OBJ_INFECT(str2, str);

    return str2;
}
