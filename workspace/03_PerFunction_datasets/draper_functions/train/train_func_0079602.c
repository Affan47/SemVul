v1h_get_NC_var(v1hs *gsp, NC_var **varpp)
{
	NC_string *strp;
	int status;
	size_t ndims;
	NC_var *varp;

	status = v1h_get_NC_string(gsp, &strp);
	if(status != ENOERR)
		return status;

	status = v1h_get_size_t(gsp, &ndims);
	if(status != ENOERR)
		goto unwind_name;

	varp = new_x_NC_var(strp, ndims);
	if(varp == NULL)
	{
		status = NC_ENOMEM;
		goto unwind_name;
	}

	status = check_v1hs(gsp, ncx_len_int(ndims));
	if(status != ENOERR)
		goto unwind_alloc;
	status = ncx_getn_int_int((const void **)(&gsp->pos),
			ndims, varp->dimids);
	if(status != ENOERR)
		goto unwind_alloc;

	status = v1h_get_NC_attrarray(gsp, &varp->attrs);
	if(status != ENOERR)
		goto unwind_alloc;

	status = v1h_get_nc_type(gsp, &varp->type);
	if(status != ENOERR)
		 goto unwind_alloc;

	status = v1h_get_size_t(gsp, &varp->len);
	if(status != ENOERR)
		 goto unwind_alloc;

	status = check_v1hs(gsp, gsp->version == 1 ? 4 : 8);
	if(status != ENOERR)
		 goto unwind_alloc;
	status = ncx_get_off_t((const void **)&gsp->pos,
			       &varp->begin, gsp->version == 1 ? 4 : 8);
	if(status != ENOERR)
		 goto unwind_alloc;

	*varpp = varp;
	return ENOERR;

unwind_alloc:
	free_NC_var(varp);
	return status;

unwind_name:
	free_NC_string(strp);
	return status;
}
