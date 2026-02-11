nv_colon(cap)
    cmdarg_T  *cap;
{
    int	    old_p_im;

#ifdef FEAT_VISUAL
    if (VIsual_active)
	nv_operator(cap);
    else
#endif
    {
	if (cap->oap->op_type != OP_NOP)
	{

	    cap->oap->motion_type = MCHAR;
	    cap->oap->inclusive = FALSE;
	}
	else if (cap->count0)
	{

	    stuffcharReadbuff('.');
	    if (cap->count0 > 1)
	    {
		stuffReadbuff((char_u *)",.+");
		stuffnumReadbuff((long)cap->count0 - 1L);
	    }
	}


	if (KeyTyped)
	    compute_cmdrow();

	old_p_im = p_im;


	do_cmdline(NULL, getexline, NULL,
			    cap->oap->op_type != OP_NOP ? DOCMD_KEEPLINE : 0);


	if (p_im != old_p_im)
	{
	    if (p_im)
		restart_edit = 'i';
	    else
		restart_edit = 0;
	}


	if (cap->oap->op_type != OP_NOP
		&& (cap->oap->start.lnum > curbuf->b_ml.ml_line_count
		    || cap->oap->start.col >
					 STRLEN(ml_get(cap->oap->start.lnum))))
	    clearopbeep(cap->oap);
    }
}
