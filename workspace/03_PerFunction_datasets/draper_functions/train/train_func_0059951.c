valuearray_find(const Slapi_Attr *a, Slapi_Value **va, const Slapi_Value *v)
{
	int i= 0;
	int found= -1;
	while(found==-1 && va!=NULL && va[i]!=NULL)
	{
		if(slapi_value_compare( a, v, va[i])==0)
		{
			found= i;
		}
		else
		{
			i++;
		}
	}
	return found;
}
