rb_ary_select_bang(VALUE ary)
{
    long i1, i2;

    RETURN_ENUMERATOR(ary, 0, 0);
    rb_ary_modify(ary);
    for (i1 = i2 = 0; i1 < RARRAY_LEN(ary); i1++) {
	VALUE v = RARRAY_PTR(ary)[i1];
	if (!RTEST(rb_yield(v))) continue;
	if (i1 != i2) {
	    rb_ary_store(ary, i2, v);
	}
	i2++;
    }

    if (RARRAY_LEN(ary) == i2) return Qnil;
    if (i2 < RARRAY_LEN(ary))
	ARY_SET_LEN(ary, i2);
    return ary;
}
