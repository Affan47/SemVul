f_listelementphylum(ID id)
{{
	ID kc_selvar_0_1 = phylum_cast<ID>(id);
	if ((kc_selvar_0_1->prod_sel() == sel_Id)) {
	    const uniqID uid = phylum_cast<const impl_ID_Id*>(kc_selvar_0_1)->uniqID_1;

	    {
		IDtype kc_selvar_1_1 = phylum_cast<IDtype>( uid->type );
		if ((kc_selvar_1_1->prod_sel() == sel_ITUserPhylum)) {
		    const phylumdeclaration pd = phylum_cast<const impl_IDtype_ITUserPhylum*>(kc_selvar_1_1)->phylumdeclaration_1;

		    {
			phylumdeclaration kc_selvar_2_1 = phylum_cast<phylumdeclaration>( pd );
			if ((kc_selvar_2_1->prod_sel() == sel_PhylumDeclaration) && (phylum_cast<const impl_phylumdeclaration_PhylumDeclaration*>(kc_selvar_2_1)->productionblock_1->prod_sel() == sel_ListAlternatives)) {
			    const ID i = phylum_cast<const impl_productionblock_ListAlternatives*>(phylum_cast<const impl_phylumdeclaration_PhylumDeclaration*>(kc_selvar_2_1)->productionblock_1)->ID_1;

			    return i;

			} else
			{
			    return f_emptyId();
			}
		    }

		} else
		{
		    return f_emptyId();
		}
	    }

	} else
	{ kc_no_default_in_with( "f_listelementphylum", __LINE__, __FILE__ );
	    return static_cast<ID>(0); }
    }

}
