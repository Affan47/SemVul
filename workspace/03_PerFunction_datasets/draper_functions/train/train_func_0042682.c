last_model_get_irf_matrix (int targ, int shock, double alpha,
			   const DATASET *dset, int *err)
{
    stacker *smatch = find_smatch(NULL);
    gretl_matrix *M = NULL;

    if (smatch == NULL || smatch->type != GRETL_OBJ_VAR) {
	*err = E_BADSTAT;
    } else {
	M = gretl_VAR_get_impulse_response(smatch->ptr, targ, shock, 0,
					   alpha, dset, err);
    }

    return M;
}
