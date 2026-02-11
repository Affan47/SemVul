resolve_attribute_state_present_to_deleted(Slapi_Entry *e, Slapi_Attr *a, Slapi_Value **valuestoupdate)
{
	const CSN *vdcsn;
	const CSN *vucsn;
	const CSN *deletedcsn;
	const CSN *adcsn= attr_get_deletion_csn(a);
	int i;
	if ( valuestoupdate != NULL && valuestoupdate[0] != NULL ) {
	for (i=0;valuestoupdate[i]!=NULL;++i) {


	    purge_attribute_state_multi_valued(a, valuestoupdate[i]);
		vdcsn= value_get_csn(valuestoupdate[i], CSN_TYPE_VALUE_DELETED);
		vucsn= value_get_csn(valuestoupdate[i], CSN_TYPE_VALUE_UPDATED);
		deletedcsn= csn_max(vdcsn, adcsn);
			if(csn_compare(vucsn,deletedcsn)<0)
			{
	        		if(!value_distinguished_at_csn(e, a, valuestoupdate[i], deletedcsn))
				{
					entry_present_value_to_deleted_value(a,valuestoupdate[i]);
				}
			}
		valuestoupdate[i]->v_csnset = NULL;
	}
	}
}
