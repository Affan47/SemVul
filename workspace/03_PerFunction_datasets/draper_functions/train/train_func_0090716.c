unparse_includefiles
#ifdef KC_USE_PROTOTYPES
(includefiles kc_p, void (*kc_printer)(char*, uview), uview kc_current_view)
#else
(kc_p, kc_printer, kc_current_view) includefiles kc_p; void (*kc_printer)KC__P((char*, uview)); uview kc_current_view;
#endif
{

	assert_includefiles(kc_p, "kc_p");
	switch((int)kc_current_view) {
	default:
	case (int)base_uview: {
		switch((int)kc_p->prod_sel) {
		case (int)sel_Consincludefiles:
			unparse_includefile( kc_p->u.Consincludefiles.includefile_1, kc_printer, kc_current_view );
			unparse_includefiles( kc_p->u.Consincludefiles.includefiles_1, kc_printer, kc_current_view );
			break;
		default:;}
		break;
	}
	}
}
