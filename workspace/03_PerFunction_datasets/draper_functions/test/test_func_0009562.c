rb_mod_ancestors(VALUE mod)
{
    VALUE p, ary = rb_ary_new();

    for (p = mod; p; p = RCLASS_SUPER(p)) {
	if (FL_TEST(p, FL_SINGLETON))
	    continue;
	if (BUILTIN_TYPE(p) == T_ICLASS) {
	    rb_ary_push(ary, RBASIC(p)->klass);
	}
	else {
	    rb_ary_push(ary, p);
	}
    }
    return ary;
}
