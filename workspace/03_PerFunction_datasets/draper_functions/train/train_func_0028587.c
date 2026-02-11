divmodv(VALUE n, VALUE d, VALUE *q, VALUE *r)
{
    VALUE tmp, ary;
    tmp = rb_funcall(n, id_divmod, 1, d);
    ary = rb_check_array_type(tmp);
    if (NIL_P(ary)) {
        rb_raise(rb_eTypeError, "unexpected divmod result: into %s",
                 rb_obj_classname(tmp));
    }
    *q = rb_ary_entry(ary, 0);
    *r = rb_ary_entry(ary, 1);
}
