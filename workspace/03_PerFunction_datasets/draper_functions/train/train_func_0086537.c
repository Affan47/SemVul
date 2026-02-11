f_visualmode(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
#ifdef FEAT_VISUAL
    char_u	str[2];

    rettv->v_type = VAR_STRING;
    str[0] = curbuf->b_visual_mode_eval;
    str[1] = NUL;
    rettv->vval.v_string = vim_strsave(str);


    if (non_zero_arg(&argvars[0]))
	curbuf->b_visual_mode_eval = NUL;
#else
    rettv->vval.v_number = 0;
#endif
}
