f_foldlevel(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv UNUSED;
{
#ifdef FEAT_FOLDING
    linenr_T	lnum;

    lnum = get_tv_lnum(argvars);
    if (lnum >= 1 && lnum <= curbuf->b_ml.ml_line_count)
	rettv->vval.v_number = foldLevel(lnum);
#endif
}
