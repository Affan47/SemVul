rewrite_phylumdeclaration
#ifdef KC_USE_PROTOTYPES
(phylumdeclaration kc_p, rview kc_current_view)
#else
(kc_p, kc_current_view) phylumdeclaration kc_p; rview kc_current_view;
#endif
{

	assert_phylumdeclaration( kc_p, "kc_p" );
	switch((int)kc_current_view) {
	default:
	case (int)base_rview: {
		switch((int)kc_p->prod_sel) {
		case (int)sel_PhylumDeclaration: {
		ID ID_1 = rewrite_ID(kc_p->u.PhylumDeclaration.ID_1, kc_current_view);
		storageoption storageoption_1 = rewrite_storageoption(kc_p->u.PhylumDeclaration.storageoption_1, kc_current_view);
		productionblock productionblock_1 = rewrite_productionblock(kc_p->u.PhylumDeclaration.productionblock_1, kc_current_view);
		Ccode_option Ccode_option_1 = rewrite_Ccode_option(kc_p->u.PhylumDeclaration.Ccode_option_1, kc_current_view);
		if ((ID_1 == kc_p->u.PhylumDeclaration.ID_1) && (storageoption_1 == kc_p->u.PhylumDeclaration.storageoption_1) && (productionblock_1 == kc_p->u.PhylumDeclaration.productionblock_1) && (Ccode_option_1 == kc_p->u.PhylumDeclaration.Ccode_option_1))
			return kc_p;
		else
			return PhylumDeclaration(ID_1, storageoption_1, productionblock_1, Ccode_option_1);
		}
		default: return kc_p;}
	}
	}
}
