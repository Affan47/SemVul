ex_swapname(eap)
    exarg_T	*eap UNUSED;
{
    if (curbuf->b_ml.ml_mfp == NULL || curbuf->b_ml.ml_mfp->mf_fname == NULL)
	MSG(_("No swap file"));
    else
	msg(curbuf->b_ml.ml_mfp->mf_fname);
}
