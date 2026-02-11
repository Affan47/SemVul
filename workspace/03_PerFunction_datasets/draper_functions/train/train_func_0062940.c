rb_ary_flatten_bang(ary)
    VALUE ary;
{
    long i = 0;
    int mod = 0;
    VALUE memo = Qnil;

    while (i<RARRAY(ary)->len) {
	VALUE ary2 = RARRAY(ary)->ptr[i];
	VALUE tmp;

	tmp = rb_check_array_type(ary2);
	if (!NIL_P(tmp)) {
	    if (NIL_P(memo)) {
		memo = rb_ary_new();
	    }
	    i += flatten(ary, i, tmp, memo);
	    mod = 1;
	}
	i++;
    }
    if (mod == 0) return Qnil;
    return ary;
}
