f_function(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	*s;

    s = get_tv_string(&argvars[0]);
    if (s == NULL || *s == NUL || VIM_ISDIGIT(*s))
	EMSG2(_(e_invarg2), s);

    else if (vim_strchr(s, AUTOLOAD_CHAR) == NULL && !function_exists(s))
	EMSG2(_("E700: Unknown function: %s"), s);
    else
    {
	rettv->vval.v_string = vim_strsave(s);
	rettv->v_type = VAR_FUNC;
    }
}
