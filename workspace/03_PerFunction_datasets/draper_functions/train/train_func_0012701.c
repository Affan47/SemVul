slapi_rdn_remove_attr(Slapi_RDN *rdn, const char *type)
{
	int result= 0;
	if(rdn->rdn!=NULL)
	{
		char *value;
		int atindex= slapi_rdn_get_index_attr(rdn, type, &value);
		if(atindex!=-1)
		{
			result= slapi_rdn_remove_index(rdn, atindex);
		}
	}
	return result;
}
