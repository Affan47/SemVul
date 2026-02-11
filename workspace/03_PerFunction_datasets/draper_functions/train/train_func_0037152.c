saved_object_get_scalar (const char *oname, int idx,
				DATASET *dset, int *err)
{
    double ret = INVALID_STAT;
    stacker *smatch;

    smatch = find_smatch(oname);

    if (smatch != NULL) {
	ret = real_get_obj_scalar(smatch->ptr, smatch->type,
				  dset, idx);
    }

    if (ret == INVALID_STAT) {
	*err = E_BADSTAT;
    }

    return ret;
}
