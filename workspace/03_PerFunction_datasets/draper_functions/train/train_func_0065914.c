Perl_clone_params_del(CLONE_PARAMS *param)
{


    PerlInterpreter *const to = param->new_perl;
    dTHXa(to);
    PerlInterpreter *const was = PERL_GET_THX;

    PERL_ARGS_ASSERT_CLONE_PARAMS_DEL;

    if (was != to) {
	PERL_SET_THX(to);
    }

    SvREFCNT_dec(param->stashes);
    if (param->unreferenced)
	unreferenced_to_tmp_stack(param->unreferenced);

    Safefree(param);

    if (was != to) {
	PERL_SET_THX(was);
    }
}
