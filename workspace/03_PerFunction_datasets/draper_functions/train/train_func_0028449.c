f_ID_of_declarator(ac_declarator d)
{{
	ac_declarator kc_selvar_0_1 = phylum_cast<ac_declarator>(d);
	if ((kc_selvar_0_1->prod_sel() == sel_AcDeclarator)) {
	    const ac_direct_declarator dd = phylum_cast<const impl_ac_declarator_AcDeclarator*>(kc_selvar_0_1)->ac_direct_declarator_1;

	    return f_ID_of_direct_decl( dd );

	} else
	{ kc_no_default_in_with( "f_ID_of_declarator", __LINE__, __FILE__ );
	    return static_cast<ID>(0); }
    }

}
