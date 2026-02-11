slapi_attr_get_valueset(const Slapi_Attr *a, Slapi_ValueSet **vs)
{
	int retVal= 0;
	if(vs!=NULL)
	{
		*vs= valueset_dup(&a->a_present_values);
	}
	return retVal;
}
