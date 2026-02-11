f_alternativeofoperator(ID oid)
{{
	ID kc_selvar_0_1 = phylum_cast<ID>(oid);
	if ((kc_selvar_0_1->prod_sel() == sel_Id)) {
	    const uniqID uid = phylum_cast<const impl_ID_Id*>(kc_selvar_0_1)->uniqID_1;

	    {
		IDtype kc_selvar_1_1 = phylum_cast<IDtype>( uid->type );
		if ((kc_selvar_1_1->prod_sel() == sel_ITUserOperator)) {
		    const alternative a = phylum_cast<const impl_IDtype_ITUserOperator*>(kc_selvar_1_1)->alternative_1;
		    return a;
		    	} else
		{
		    return 0;
		}
	    }

	} else
	{ kc_no_default_in_with( "f_alternativeofoperator", __LINE__, __FILE__ );
	    return static_cast<alternative>(0); }
    }

}
