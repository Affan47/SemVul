VAR_add_models (GRETL_VAR *var, const DATASET *dset)
{
    int n = var->neqns;
    int i, err = 0;

    if (var->models != NULL) {
	for (i=0; i<n; i++) {
	    clear_model(var->models[i]);
	}
    } else {
	var->models = gretl_model_array_new(n);
	if (var->models == NULL) {
	    err = E_ALLOC;
	}
    }

    if (var->models != NULL) {
	for (i=0; i<n; i++) {
	    gretl_model_smpl_init(var->models[i], dset);
	}
    }

    return err;
}
