attr_value_find_wsi(Slapi_Attr *a, const struct berval *bval, Slapi_Value **value)
{
	int retVal=0;
	struct ava ava;

	PR_ASSERT(a!=NULL);
	PR_ASSERT(value!=NULL);


	ava.ava_type = a->a_type;
	ava.ava_value = *bval;
	ava.ava_private = NULL;
	retVal = plugin_call_syntax_filter_ava_sv(a, LDAP_FILTER_EQUALITY, &ava, value, 0 );

	if(retVal==0)
	{

		retVal= VALUE_PRESENT;
	}
	else
	{
		retVal = plugin_call_syntax_filter_ava_sv(a, LDAP_FILTER_EQUALITY, &ava, value, 1 );
		if(retVal==0)
		{

			retVal= VALUE_DELETED;
		}
		else
		{

			retVal= VALUE_NOTFOUND;
		}
	}

	return retVal;
}
