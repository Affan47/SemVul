cobsavenv (struct cobjmp_buf *jbuf)
{
	if (unlikely(!jbuf)) {
		cob_runtime_error ("NULL name parameter passed to 'cobsavenv'");
		cob_stop_run (1);
	}
	if (cobjmp_primed) {
		cob_runtime_error ("Multiple call to 'cobsetjmp'");
		cob_stop_run (1);
	}
	cobjmp_primed = 1;
	return jbuf->cbj_jmp_buf;
}
