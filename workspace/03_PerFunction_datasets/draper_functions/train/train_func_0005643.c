last_model_get_vcv_type (void)
{
    stacker *smatch = find_smatch(NULL);
    static char ret[16];

    *ret = '\0';

    if (smatch != NULL && smatch->type == GRETL_OBJ_EQN) {
	const MODEL *pmod = smatch->ptr;
	VCVInfo *vi;

	vi = gretl_model_get_data(pmod, "vcv_info");

	if (vi != NULL && vi->vmaj == VCV_ML) {
	    if (vi->vmin == ML_HESSIAN) {
		strcpy(ret, "Hessian");
	    } else if (vi->vmin == ML_OP) {
		strcpy(ret, "OPG");
	    } else if (vi->vmin == ML_QML) {
		strcpy(ret, "Sandwich");
	    }
	}
    }

    return (*ret != '\0')? ret : NULL;
}
