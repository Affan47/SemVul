unparse_fnclass
#ifdef KC_USE_PROTOTYPES
(fnclass kc_p, void (*kc_printer)(char*, uview), uview kc_current_view)
#else
(kc_p, kc_printer, kc_current_view) fnclass kc_p; void (*kc_printer)KC__P((char*, uview)); uview kc_current_view;
#endif
{

	assert_fnclass(kc_p, "kc_p");
	switch((int)kc_current_view) {
	case (int)view_gen_fnk_c: {
		if (( kc_p->prod_sel == sel_GlobalFn)) {
#line 7436 "../gen.k"

#line 15582 "unpk.c"
		} else
		if (( kc_p->prod_sel == sel_LocalFn)) {
		{ (*kc_printer)("static ", kc_current_view); }
		} else
		goto kc_unparsing_default;
		break;
	}
	default:
	kc_unparsing_default:
	case (int)base_uview: {
		switch((int)kc_p->prod_sel) {
		case (int)sel_LocalFn:
			unparse_casestring( kc_p->u.LocalFn.casestring_1, kc_printer, kc_current_view );
			break;
		default:;}
		break;
	}
	}
}
