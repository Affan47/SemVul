update_ref_value(hid_t obj_id, H5R_type_t ref_type, void *ref_in,
		hid_t fid_out, void *ref_out, trav_table_t *travt)
{
	herr_t ret = -1;
	const char* ref_obj_name;
	hid_t space_id=-1, ref_obj_id=-1;

    ref_obj_id = H5Rdereference(obj_id, ref_type, ref_in);
	if (ref_obj_id<0)
		goto done;

	ref_obj_name = MapIdToName(ref_obj_id, travt);
	if (ref_obj_name == NULL)
		goto done;

	if (ref_type == H5R_DATASET_REGION) {
		space_id = H5Rget_region(obj_id, H5R_DATASET_REGION, ref_in);
		if (space_id < 0)
			goto done;
	}

    ret = H5Rcreate(ref_out, fid_out, ref_obj_name, ref_type, space_id);

    if (ret < 0)
    	goto done;

	ret = 0;

done:
    H5E_BEGIN_TRY {
    	H5Sclose(space_id);
    	H5Oclose(ref_obj_id);
    } H5E_END_TRY;

	return ret;
}
