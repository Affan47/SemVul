unparse_ac_direct_abstract_declarator_option
#ifdef KC_USE_PROTOTYPES
(ac_direct_abstract_declarator_option kc_p, void (*kc_printer)(char*, uview), uview kc_current_view)
#else
(kc_p, kc_printer, kc_current_view) ac_direct_abstract_declarator_option kc_p; void (*kc_printer)KC__P((char*, uview)); uview kc_current_view;
#endif
{

	assert_ac_direct_abstract_declarator_option(kc_p, "kc_p");
	switch((int)kc_current_view) {
	default:
	case (int)base_uview: {
		if (( kc_p->prod_sel == sel_Yesac_direct_abstract_declarator)) {
#line 7589 "../gen.k"
		ac_direct_abstract_declarator dad =  kc_p->u.Yesac_direct_abstract_declarator.ac_direct_abstract_declarator_1;
		unparse_ac_direct_abstract_declarator(dad, kc_printer, kc_current_view);
		} else
		switch((int)kc_p->prod_sel) {
		case (int)sel_Yesac_direct_abstract_declarator:
			unparse_ac_direct_abstract_declarator( kc_p->u.Yesac_direct_abstract_declarator.ac_direct_abstract_declarator_1, kc_printer, kc_current_view );
			break;
		default:;}
		break;
	}
	}
}
