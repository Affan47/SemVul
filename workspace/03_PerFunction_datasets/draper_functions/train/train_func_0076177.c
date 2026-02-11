rb_reg_search(VALUE re, VALUE str, long pos, int reverse)
{
    long result;
    VALUE match;
    struct re_registers regi, *regs = &regi;
    char *range = RSTRING_PTR(str);
    regex_t *reg;
    int tmpreg;

    if (pos > RSTRING_LEN(str) || pos < 0) {
	rb_backref_set(Qnil);
	return -1;
    }

    reg = rb_reg_prepare_re(re, str);
    tmpreg = reg != RREGEXP(re)->ptr;
    if (!tmpreg) RREGEXP(re)->usecnt++;

    match = rb_backref_get();
    if (!NIL_P(match)) {
	if (FL_TEST(match, MATCH_BUSY)) {
	    match = Qnil;
	}
	else {
	    regs = RMATCH_REGS(match);
	}
    }
    if (NIL_P(match)) {
	MEMZERO(regs, struct re_registers, 1);
    }
    if (!reverse) {
	range += RSTRING_LEN(str);
    }
    result = onig_search(reg,
			 (UChar*)(RSTRING_PTR(str)),
			 ((UChar*)(RSTRING_PTR(str)) + RSTRING_LEN(str)),
			 ((UChar*)(RSTRING_PTR(str)) + pos),
			 ((UChar*)range),
			 regs, ONIG_OPTION_NONE);
    if (!tmpreg) RREGEXP(re)->usecnt--;
    if (tmpreg) {
	if (RREGEXP(re)->usecnt) {
	    onig_free(reg);
	}
	else {
	    onig_free(RREGEXP(re)->ptr);
	    RREGEXP(re)->ptr = reg;
	}
    }
    if (result < 0) {
	if (regs == &regi)
	    onig_region_free(regs, 0);
	if (result == ONIG_MISMATCH) {
	    rb_backref_set(Qnil);
	    return result;
	}
	else {
	    onig_errmsg_buffer err = "";
	    onig_error_code_to_str((UChar*)err, (int)result);
	    rb_reg_raise(RREGEXP_SRC_PTR(re), RREGEXP_SRC_LEN(re), err, re);
	}
    }

    if (NIL_P(match)) {
	match = match_alloc(rb_cMatch);
	onig_region_copy(RMATCH_REGS(match), regs);
	onig_region_free(regs, 0);
    }
    else {
	if (rb_safe_level() >= 3)
	    OBJ_TAINT(match);
	else
	    FL_UNSET(match, FL_TAINT);
    }

    RMATCH(match)->str = rb_str_new4(str);
    RMATCH(match)->regexp = re;
    RMATCH(match)->rmatch->char_offset_updated = 0;
    rb_backref_set(match);

    OBJ_INFECT(match, re);
    OBJ_INFECT(match, str);

    return result;
}
