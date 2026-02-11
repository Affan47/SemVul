syn_patternchainitem(patternchainitem a_patternchainitem, path a_path)
{{
	patternchainitem kc_selvar_0_1 = phylum_cast<patternchainitem>(a_patternchainitem);
	if ((kc_selvar_0_1->prod_sel() == sel_PatternchainitemDollarid)) {
	    const ID id = phylum_cast<const impl_patternchainitem_PatternchainitemDollarid*>(kc_selvar_0_1)->ID_1;

	    elem_patternrepresentation tmp = PRBinding( a_path, id );
	    tmp->type = a_patternchainitem->type;
	    return Conspatternrepresentation(
		tmp,
		Nilpatternrepresentation()
	    );

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_PatternchainitemGroup)) {

	    v_report( NonFatal(  FileLine( a_patternchainitem->file, a_patternchainitem->line ),
		    Problem1S( "Internal Error: PatternchainitemGroup was not handled correctly" )));
	    return Nilpatternrepresentation();

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_PatternchainitemOutmost)) {
	    const outmostpattern a_outmostpattern = phylum_cast<const impl_patternchainitem_PatternchainitemOutmost*>(kc_selvar_0_1)->outmostpattern_1;

	    return syn_outmostpattern( a_outmostpattern, a_path );

	} else
	{ kc_no_default_in_with( "syn_patternchainitem", __LINE__, __FILE__ );
	    return static_cast<patternrepresentation>(0); }
    }

}
