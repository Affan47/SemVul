rb_ary_subseq(ary, beg, len)
    VALUE ary;
    long beg, len;
{
    VALUE klass, ary2, shared;
    VALUE *ptr;

    if (beg > RARRAY(ary)->len) return Qnil;
    if (beg < 0 || len < 0) return Qnil;

    if (beg + len > RARRAY(ary)->len) {
	len = RARRAY(ary)->len - beg;
	if (len < 0)
	    len = 0;
    }
    klass = rb_obj_class(ary);
    if (len == 0) return ary_new(klass, 0);

    shared = ary_make_shared(ary);
    ptr = RARRAY(ary)->ptr;
    ary2 = ary_alloc(klass);
    RARRAY(ary2)->ptr = ptr + beg;
    RARRAY(ary2)->len = len;
    RARRAY(ary2)->aux.shared = shared;
    FL_SET(ary2, ELTS_SHARED);

    return ary2;
}
