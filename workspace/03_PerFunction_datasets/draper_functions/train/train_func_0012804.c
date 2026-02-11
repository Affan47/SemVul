slap_create_context_csn_entry(
	Backend *be,
	struct berval *context_csn )
{
	Entry* e;

	struct berval bv;

	e = entry_alloc();

	attr_merge( e, slap_schema.si_ad_objectClass,
		ocbva, NULL );
	attr_merge_one( e, slap_schema.si_ad_structuralObjectClass,
		&ocbva[1], NULL );
	attr_merge_one( e, slap_schema.si_ad_cn,
		(struct berval *)&slap_ldapsync_bv, NULL );

	if ( context_csn ) {
		attr_merge_one( e, slap_schema.si_ad_contextCSN,
			context_csn, NULL );
	}

	BER_BVSTR( &bv, "{}" );
	attr_merge_one( e, slap_schema.si_ad_subtreeSpecification, &bv, NULL );

	build_new_dn( &e->e_name, &be->be_nsuffix[0],
		(struct berval *)&slap_ldapsync_cn_bv, NULL );
	ber_dupbv( &e->e_nname, &e->e_name );

	return e;
}
