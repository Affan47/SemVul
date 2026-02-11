group_by_i(VALUE i, VALUE hash, int argc, VALUE *argv)
{
    VALUE group;
    VALUE values;

    ENUM_WANT_SVALUE();

    group = rb_yield(i);
    values = rb_hash_aref(hash, group);
    if (NIL_P(values)) {
	values = rb_ary_new3(1, i);
	rb_hash_aset(hash, group, values);
    }
    else {
	rb_ary_push(values, i);
    }
    return Qnil;
}
