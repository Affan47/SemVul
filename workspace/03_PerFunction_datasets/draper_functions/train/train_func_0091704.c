vdac_sniff_attribute(Slapi_ValueSet *vs, Slapi_Attr *a, const CSN *csn, const CSN *most_recent_mdcsn)
{
	Slapi_Value *v;
	int i= slapi_attr_first_value( a, &v );
	while(i!=-1)
	{
		most_recent_mdcsn= vdac_sniff_value( vs, v, csn, most_recent_mdcsn );
		i= slapi_attr_next_value( a, i, &v );
	}
	i= attr_first_deleted_value( a, &v );
	while(i!=-1)
	{
		most_recent_mdcsn= vdac_sniff_value( vs, v, csn, most_recent_mdcsn );
		i= attr_next_deleted_value( a, i, &v );
	}
	return most_recent_mdcsn;
}
