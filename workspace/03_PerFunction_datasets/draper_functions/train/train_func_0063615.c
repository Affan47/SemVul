VpGetPrecLimit(void)
{
    VALUE const vlimit = rb_thread_local_aref(
	rb_thread_current(),
	id_BigDecimal_precision_limit
    );

    if (NIL_P(vlimit)) {
	rmpd_set_thread_local_precision_limit(RMPD_PRECISION_LIMIT_DEFAULT);
	return RMPD_PRECISION_LIMIT_DEFAULT;
    }

    return NUM2SIZET(vlimit);
}
