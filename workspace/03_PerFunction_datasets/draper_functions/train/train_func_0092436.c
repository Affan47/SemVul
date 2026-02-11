rb_str_rstrip_bang(str)
    VALUE str;
{
    char *s, *t, *e;

    s = RSTRING(str)->ptr;
    if (!s || RSTRING(str)->len == 0) return Qnil;
    e = t = s + RSTRING(str)->len;


    while (s < t && t[-1] == '\0') t--;


    while (s < t && ISSPACE(*(t-1))) t--;

    if (t < e) {
	rb_str_modify(str);
	RSTRING(str)->len = t-s;
	RSTRING(str)->ptr[RSTRING(str)->len] = '\0';
	return str;
    }
    return Qnil;
}
