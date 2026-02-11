boot_new (const MODEL *pmod,
		       const DATASET *dset,
		       int B, gretlopt opt,
		       int *err)
{
    boot *bs;

    bs = malloc(sizeof *bs);
    if (bs == NULL) {
	return NULL;
    }

    bs->ldv = NULL;

    *err = make_boot_ldvinfo(bs, pmod, dset);
    if (*err) {
	free(bs);
	return NULL;
    }

    bs->y = NULL;
    bs->X = NULL;
    bs->b0 = NULL;
    bs->u0 = NULL;
    bs->w = NULL;

    bs->R = NULL;
    bs->q = NULL;

    if (make_model_matrices(bs, pmod, dset)) {
	boot_destroy(bs);
	return NULL;
    }

    bs->flags = make_bs_flags(opt);

    bs->mci = pmod->ci;
    bs->a = 0.05;
    bs->B = maybe_adjust_B(B, bs->a, bs->flags);

    bs->p = 0;
    bs->g = 0;

    *bs->vname = '\0';

    bs->SE = NADBL;
    bs->point = NADBL;
    bs->se0 = NADBL;
    bs->test0 = NADBL;
    bs->b_p = NADBL;
    bs->pval = NADBL;

    bs->k = bs->X->cols;
    bs->T = bs->X->rows;

    return bs;
}
