Perl_gp_ref(pTHX_ GP *gp)
{
    dVAR;
    if (!gp)
	return NULL;
    gp->gp_refcnt++;
    if (gp->gp_cv) {
	if (gp->gp_cvgen) {


	    SvREFCNT_dec_NN(gp->gp_cv);
	    gp->gp_cv = NULL;
	    gp->gp_cvgen = 0;
	}
    }
    return gp;
}
