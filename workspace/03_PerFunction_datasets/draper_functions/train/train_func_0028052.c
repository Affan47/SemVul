rb_reg_equal(VALUE re1, VALUE re2)
{
    if (re1 == re2) return Qtrue;
    if (TYPE(re2) != T_REGEXP) return Qfalse;
    rb_reg_check(re1); rb_reg_check(re2);
    if (FL_TEST(re1, KCODE_FIXED) != FL_TEST(re2, KCODE_FIXED)) return Qfalse;
    if (RREGEXP(re1)->ptr->options != RREGEXP(re2)->ptr->options) return Qfalse;
    if (RREGEXP_SRC_LEN(re1) != RREGEXP_SRC_LEN(re2)) return Qfalse;
    if (ENCODING_GET(re1) != ENCODING_GET(re2)) return Qfalse;
    if (memcmp(RREGEXP_SRC_PTR(re1), RREGEXP_SRC_PTR(re2), RREGEXP_SRC_LEN(re1)) == 0) {
	return Qtrue;
    }
    return Qfalse;
}
