f_winrestcmd(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv;
{
#ifdef FEAT_WINDOWS
    win_T	*wp;
    int		winnr = 1;
    garray_T	ga;
    char_u	buf[50];

    ga_init2(&ga, (int)sizeof(char), 70);
    for (wp = firstwin; wp != NULL; wp = wp->w_next)
    {
	sprintf((char *)buf, "%dresize %d|", winnr, wp->w_height);
	ga_concat(&ga, buf);
# ifdef FEAT_VERTSPLIT
	sprintf((char *)buf, "vert %dresize %d|", winnr, wp->w_width);
	ga_concat(&ga, buf);
# endif
	++winnr;
    }
    ga_append(&ga, NUL);

    rettv->vval.v_string = ga.ga_data;
#else
    rettv->vval.v_string = NULL;
#endif
    rettv->v_type = VAR_STRING;
}
