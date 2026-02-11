add_predicates_to_patternrepresentations(patternrepresentations a_patternreps)
{{
	patternrepresentations kc_selvar_0_1 = phylum_cast<patternrepresentations>(a_patternreps);
	if ((kc_selvar_0_1->prod_sel() == sel_Conspatternrepresentations)) {
	    const patternrepresentation a_patternrep = (kc_selvar_0_1)->patternrepresentation_1;
	    const patternrepresentations r_patternreps = (kc_selvar_0_1)->patternrepresentations_1;

	    patternrepresentation tmp;
	    v_resetbindingidmarks();
	    tmp = add_predicates( a_patternrep );
	    return Conspatternrepresentations(
		concat( a_patternrep, tmp ),
		add_predicates_to_patternrepresentations( r_patternreps )
	    );

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Nilpatternrepresentations)) {

	    return Nilpatternrepresentations();

	} else
	{ kc_no_default_in_with( "add_predicates_to_patternrepresentations", __LINE__, __FILE__ );
	    return static_cast<patternrepresentations>(0); }
    }

}
