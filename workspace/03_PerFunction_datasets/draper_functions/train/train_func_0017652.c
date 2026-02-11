VSB_clear(struct vsb *s)
{

	assert_VSB_integrity(s);


	VSB_CLEARFLAG(s, VSB_FINISHED);
	s->s_error = 0;
	s->s_len = 0;
}
