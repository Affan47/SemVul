rb_reg_init_copy(VALUE copy, VALUE re)
{
    onig_errmsg_buffer err = "";
    const char *s;
    long len;

    if (copy == re) return copy;
    rb_check_frozen(copy);

    if (!rb_obj_is_instance_of(re, rb_obj_class(copy))) {
	rb_raise(rb_eTypeError, "wrong argument type");
    }
    rb_reg_check(re);
    s = RREGEXP_SRC_PTR(re);
    len = RREGEXP_SRC_LEN(re);
    if (rb_reg_initialize(copy, s, len, rb_enc_get(re), rb_reg_options(re),
		err, NULL, 0) != 0) {
	rb_reg_raise(s, len, err, re);
    }
    return copy;
}
