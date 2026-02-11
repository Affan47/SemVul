kc_do_last_phylum
#ifdef KC_USE_PROTOTYPES
(kc_voidptr_t kc_p, kc_enum_phyla kc_phylum)
#else
(kc_p, kc_phylum) kc_voidptr_t kc_p; kc_enum_phyla kc_phylum;
#endif
{	boolean kc_not_ready = True;
	kc_voidptr_t kc_tmp = (kc_voidptr_t)0;
	kc_enum_operators kc_prodsel;
	KC_PHYLUM_INFO *kc_phy_info = &kc_PhylumInfo[(int)kc_phylum];
	KC_OPERATOR_INFO *kc_lastop_info = &kc_OperatorInfo[(int)kc_phy_info->last_operator];

	assertPhylum(((casestring)kc_p),"kc_p",kc_phylum);
	if (((casestring)kc_p)->prod_sel == kc_phy_info->first_operator) {
		(void)fflush(stdout); (void)fprintf(stderr, kc_error_last_with_nil_argument, kc_phy_info->name,  kc_phy_info->name); exit( 1 );
	}
	while(kc_not_ready) {

		assertPhylum(((casestring)kc_p),"kc_p",kc_phylum);
		kc_prodsel = ((casestring)kc_p)->prod_sel;
		if (kc_prodsel == kc_phy_info->first_operator) {
			kc_not_ready=False;
		} else if (kc_prodsel == kc_phy_info->last_operator) {
			kc_tmp = (kc_voidptr_t)KC_SUBPHYLUM(kc_p, kc_lastop_info->suboffset[0]);
			kc_p = (kc_voidptr_t)KC_SUBPHYLUM(kc_p, kc_lastop_info->suboffset[1]);
		} else {
			kc_invalid_operator(kc_error_last, kc_phylum, __LINE__, __FILE__, (int)kc_prodsel);
	}	}
	return kc_tmp;
}
