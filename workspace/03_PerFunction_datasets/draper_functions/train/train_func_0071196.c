f_phylumofpatternrepresentation(patternrepresentation a_patrep)
{
    {
	patternrepresentation kc_selvar_0_1 = phylum_cast<patternrepresentation>( a_patrep );
	if ((kc_selvar_0_1->prod_sel() == sel_Conspatternrepresentation)) {
	    const elem_patternrepresentation a_patrep_elem = (kc_selvar_0_1)->elem_patternrepresentation_1;
	    const patternrepresentation r_patrep = (kc_selvar_0_1)->patternrepresentation_1;

	    {
		elem_patternrepresentation kc_selvar_1_1 = phylum_cast<elem_patternrepresentation>( a_patrep_elem );
		if ((kc_selvar_1_1->prod_sel() == sel_PROperPredicate)) {
		    const ID id = phylum_cast<const impl_elem_patternrepresentation_PROperPredicate*>(kc_selvar_1_1)->ID_1;

		    return f_phylumofoperator( id );

		} else
		{

		    return f_phylumofpatternrepresentation( r_patrep );

		}
	    }

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Nilpatternrepresentation)) {

	    return f_emptyId();

	} else
	{ kc_no_default_in_with( "f_phylumofpatternrepresentation", __LINE__, __FILE__ );
	    return static_cast<ID>(0); }
    }

}
