value_init(Slapi_Value *v, const struct berval *bval,CSNType t,const CSN *csn)
{
	PR_ASSERT(v!=NULL);
	memset(v,0,sizeof(Slapi_Value));
	if(csn!=NULL)
	{
		value_update_csn(v,t,csn);
	}
	slapi_value_set_berval(v,bval);
    return v;
}
