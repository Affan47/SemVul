f_do_get_bindings(patternrepresentation a_patternrep)
{{
	patternrepresentation kc_selvar_0_1 = phylum_cast<patternrepresentation>(a_patternrep);
	if ((kc_selvar_0_1->prod_sel() == sel_Conspatternrepresentation)) {
	    const elem_patternrepresentation a_patternrep_elem = (kc_selvar_0_1)->elem_patternrepresentation_1;
	    const patternrepresentation r_patternrep = (kc_selvar_0_1)->patternrepresentation_1;

	    {
		elem_patternrepresentation kc_selvar_1_1 = phylum_cast<elem_patternrepresentation>( a_patternrep_elem );
		if ((kc_selvar_1_1->prod_sel() == sel_PRNonLeafBinding)) {
		    const ID id = phylum_cast<const impl_elem_patternrepresentation_PRNonLeafBinding*>(kc_selvar_1_1)->ID_1;

		    if (! f_bindingidmarked( id )) {
			v_markbindingid( id );
			return Conspatternrepresentation( a_patternrep_elem, f_do_get_bindings( r_patternrep ) );
		    } else {
			return f_do_get_bindings( r_patternrep );
		    }
		    	} else
		    if ((kc_selvar_1_1->prod_sel() == sel_PRBinding)) {
		    const ID id = phylum_cast<const impl_elem_patternrepresentation_PRBinding*>(kc_selvar_1_1)->ID_1;

		    if (! f_bindingidmarked( id )) {
			v_markbindingid( id );
			return Conspatternrepresentation( a_patternrep_elem, f_do_get_bindings( r_patternrep ) );
		    } else {
			return f_do_get_bindings( r_patternrep );
		    }
		    	} else
		{

		    return f_do_get_bindings( r_patternrep );

		}
	    }

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Nilpatternrepresentation)) {

	    return Nilpatternrepresentation();

	} else
	{ kc_no_default_in_with( "f_do_get_bindings", __LINE__, __FILE__ );
	    return static_cast<patternrepresentation>(0); }
    }

}
