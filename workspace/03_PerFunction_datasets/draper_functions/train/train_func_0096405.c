gretl_model_get_scalar (const MODEL *pmod, ModelDataIndex idx,
			       DATASET *dset, int *err)
{
    double x = NADBL;

    if (pmod == NULL) {
	*err = E_BADSTAT;
	return x;
    }

    if (idx == M_GMMCRIT && pmod->ci != GMM) {
	*err = E_BADSTAT;
	return x;
    }

    switch (idx) {
    case M_ESS:
    case M_GMMCRIT:
	x = pmod->ess;
	break;
    case M_RSQ:
	x = pmod->rsq;
	break;
    case M_LNL:
	x = pmod->lnL;
	break;
    case M_AIC:
	x = pmod->criterion[C_AIC];
	break;
    case M_BIC:
	x = pmod->criterion[C_BIC];
	break;
    case M_HQC:
	x = pmod->criterion[C_HQC];
	break;
    case M_SIGMA:
	x = pmod->sigma;
	break;
    case M_TRSQ:
	if (!na(pmod->rsq)) {
	    x = pmod->nobs * pmod->rsq;
	}
	break;
    case M_DF:
	x = (double) pmod->dfd;
	break;
    case M_NCOEFF:
	x = (double) pmod->ncoeff;
	break;
    case M_T:
	x = (double) pmod->nobs;
	break;
    case M_DWPVAL:
	x = get_DW_pvalue_for_model(pmod, dset, err);
	break;
    case M_FSTT:
	x = pmod->fstt;
	break;
    case M_CHISQ:
	x = pmod->chisq;
	break;
    default:
	break;
    }

    if (na(x)) {
	*err = E_BADSTAT;
    }

    return x;
}
