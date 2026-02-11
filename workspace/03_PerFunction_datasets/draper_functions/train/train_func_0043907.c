get_winnr(tp, argvar)
    tabpage_T	*tp;
    typval_T	*argvar;
{
    win_T	*twin;
    int		nr = 1;
    win_T	*wp;
    char_u	*arg;

    twin = (tp == curtab) ? curwin : tp->tp_curwin;
    if (argvar->v_type != VAR_UNKNOWN)
    {
	arg = get_tv_string_chk(argvar);
	if (arg == NULL)
	    nr = 0;
	else if (STRCMP(arg, "$") == 0)
	    twin = (tp == curtab) ? lastwin : tp->tp_lastwin;
	else if (STRCMP(arg, "#") == 0)
	{
	    twin = (tp == curtab) ? prevwin : tp->tp_prevwin;
	    if (twin == NULL)
		nr = 0;
	}
	else
	{
	    EMSG2(_(e_invexpr2), arg);
	    nr = 0;
	}
    }

    if (nr > 0)
	for (wp = (tp == curtab) ? firstwin : tp->tp_firstwin;
					      wp != twin; wp = wp->w_next)
	{
	    if (wp == NULL)
	    {

		nr = 0;
		break;
	    }
	    ++nr;
	}
    return nr;
}
