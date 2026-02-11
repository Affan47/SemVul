NC3_inq_att(int ncid,
	int varid,
	const char *name,
	nc_type *datatypep,
	size_t *lenp)
{
	int status;
	NC_attr *attrp;

	status = NC_lookupattr(ncid, varid, name, &attrp);
	if(status != NC_NOERR)
		return status;

	if(datatypep != NULL)
		*datatypep = attrp->type;
	if(lenp != NULL)
		*lenp = attrp->nelems;

	return NC_NOERR;
}
