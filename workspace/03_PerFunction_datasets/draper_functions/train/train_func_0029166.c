rewrite_unparsedeclaration
#ifdef KC_USE_PROTOTYPES
(unparsedeclaration kc_p, rview kc_current_view)
#else
(kc_p, kc_current_view) unparsedeclaration kc_p; rview kc_current_view;
#endif
{

	assert_unparsedeclaration( kc_p, "kc_p" );
	switch((int)kc_current_view) {
	default:
	case (int)base_rview: {
		switch((int)kc_p->prod_sel) {
		case (int)sel_UnparseDeclaration: {
		outmostpatterns outmostpatterns_1 = rewrite_outmostpatterns(kc_p->u.UnparseDeclaration.outmostpatterns_1, kc_current_view);
		unparseclauses unparseclauses_1 = rewrite_unparseclauses(kc_p->u.UnparseDeclaration.unparseclauses_1, kc_current_view);
		if ((outmostpatterns_1 == kc_p->u.UnparseDeclaration.outmostpatterns_1) && (unparseclauses_1 == kc_p->u.UnparseDeclaration.unparseclauses_1))
			return kc_p;
		else
			return UnparseDeclaration(outmostpatterns_1, unparseclauses_1);
		}
		default: return kc_p;}
	}
	}
}
