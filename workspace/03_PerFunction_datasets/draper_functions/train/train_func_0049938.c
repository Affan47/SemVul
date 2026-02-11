syn_patternchains_fileline(patternchains a_patternchains, casestring a_file, int a_line)
{{
	patternchains kc_selvar_0_1 = phylum_cast<patternchains>(a_patternchains);
	if ((kc_selvar_0_1->prod_sel() == sel_Nilpatternchains)) {

	    kc_selvar_0_1->file = a_file;
	    kc_selvar_0_1->line = a_line;
	    return a_patternchains;

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Conspatternchains)) {
	    const patternchain h = (kc_selvar_0_1)->patternchain_1;
	    const patternchains t = (kc_selvar_0_1)->patternchains_1;

	    syn_patternchains_fileline( t, a_file, a_line  );
	    syn_patternchain_fileline( h, t->file, t->line );
	    kc_selvar_0_1->file = h->file;
	    kc_selvar_0_1->line = h->line;
	    return a_patternchains;

	} else
	{ kc_no_default_in_with( "syn_patternchains_fileline", __LINE__, __FILE__ );
	    return static_cast<patternchains>(0); }
    }

}
