rb_ary_or(VALUE ary1, VALUE ary2)
{
    VALUE hash, ary3, v;
    st_data_t vv;
    long i;

    ary2 = to_ary(ary2);
    ary3 = rb_ary_new2(RARRAY_LEN(ary1)+RARRAY_LEN(ary2));
    hash = ary_add_hash(ary_make_hash(ary1), ary2);

    for (i=0; i<RARRAY_LEN(ary1); i++) {
	vv = (st_data_t)(v = rb_ary_elt(ary1, i));
	if (st_delete(RHASH_TBL(hash), &vv, 0)) {
	    rb_ary_push(ary3, v);
	}
    }
    for (i=0; i<RARRAY_LEN(ary2); i++) {
	vv = (st_data_t)(v = rb_ary_elt(ary2, i));
	if (st_delete(RHASH_TBL(hash), &vv, 0)) {
	    rb_ary_push(ary3, v);
	}
    }
    ary_recycle_hash(hash);
    return ary3;
}
