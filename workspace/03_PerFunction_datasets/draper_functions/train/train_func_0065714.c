recursive_cmp(VALUE ary1, VALUE ary2, int recur)
{
    long i, len;

    if (recur) return Qundef;
    len = RARRAY_LEN(ary1);
    if (len > RARRAY_LEN(ary2)) {
	len = RARRAY_LEN(ary2);
    }
    for (i=0; i<len; i++) {
	VALUE v = rb_funcall(rb_ary_elt(ary1, i), id_cmp, 1, rb_ary_elt(ary2, i));
	if (v != INT2FIX(0)) {
	    return v;
	}
    }
    return Qundef;
}
