f_member_class_info(ac_declaration_specifiers ds, casestring fn)
{{
	ac_declaration_specifiers kc_selvar_0_1 = phylum_cast<ac_declaration_specifiers>(ds);
	if ((kc_selvar_0_1->prod_sel() == sel_Consac_declaration_specifiers)) {
	    const ac_declaration_specifier h = (kc_selvar_0_1)->ac_declaration_specifier_1;
	    const ac_declaration_specifiers t = (kc_selvar_0_1)->ac_declaration_specifiers_1;

	    if (f_static_in_ac_decl_spec( h )) {
		return StaticFn( fn );
	    } else {
		return f_member_class_info( t, fn);
	    }

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Nilac_declaration_specifiers)) {
	    return MemberFn();
	    	} else
	{ kc_no_default_in_with( "f_member_class_info", __LINE__, __FILE__ );
	    return static_cast<fnclass>(0); }
    }

}
