fill_added(NC *gnu, NC *old)
{
	NC_var ** const gnu_varpp = (NC_var **)gnu->vars.value;
	int varid = (int)old->vars.nelems;

	for(; varid < (int)gnu->vars.nelems; varid++)
	{
		const NC_var *const gnu_varp = *(gnu_varpp + varid);
		if(IS_RECVAR(gnu_varp))
		{

			continue;
		}

		{
		const int status = fill_NC_var(gnu, gnu_varp, gnu_varp->len, 0);
		if(status != NC_NOERR)
			return status;
		}
	}

	return NC_NOERR;
}
