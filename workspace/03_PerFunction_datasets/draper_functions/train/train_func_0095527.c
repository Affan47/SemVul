entry_present_value_to_zapped_value(Slapi_Attr *a, Slapi_Value *v)
{
	if(v!=NULL)
	{
		Slapi_Value *r= valueset_remove_value(a, &a->a_present_values, v);
		if(r!=NULL)
		{
			slapi_value_free(&r);
		}
	}
	return LDAP_SUCCESS;
}
