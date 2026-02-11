omit_test (MODEL *pmod, const int *omitvars,
	       DATASET *dset, gretlopt opt, PRN *prn)
{
    int err = omit_test_precheck(pmod, opt);

    if (!err) {
	err = wald_omit_test(omitvars, pmod, dset, opt, prn);
    }

    return err;
}
