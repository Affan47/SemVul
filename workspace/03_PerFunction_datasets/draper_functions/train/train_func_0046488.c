rlm_destroy_perl(PerlInterpreter *perl)
{
	void	**handles;

	dTHXa(perl);
	PERL_SET_CONTEXT(perl);

	handles = rlm_perl_get_handles(aTHX);
	rlm_perl_destruct(perl);
	rlm_perl_close_handles(handles);
}
