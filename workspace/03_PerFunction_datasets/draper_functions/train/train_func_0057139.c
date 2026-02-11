nssov_dn2uid(Operation *op,nssov_info *ni,struct berval *dn,struct berval *uid)
{
	nssov_mapinfo *mi = &ni->ni_maps[NM_passwd];
	AttributeDescription *ad = mi->mi_attrs[UID_KEY].an_desc;
	Entry *e;


	if (!dn->bv_len)
		return 0;

	if (!strncmp(dn->bv_val,ad->ad_cname.bv_val,ad->ad_cname.bv_len) &&
		dn->bv_val[ad->ad_cname.bv_len] == '=')
	{
		struct berval bv, rdn;
		dnRdn(dn, &rdn);

		bv.bv_val = dn->bv_val + ad->ad_cname.bv_len + 1;
		bv.bv_len = rdn.bv_len - ad->ad_cname.bv_len - 1;
		if (!isvalidusername(&bv))
			return 0;
		ber_dupbv_x( uid, &bv, op->o_tmpmemctx );
		return 1;
	}

	if (be_entry_get_rw( op, dn, NULL, ad, 0, &e) == LDAP_SUCCESS)
	{
		Attribute *a = attr_find(e->e_attrs, ad);
		if (a) {
			ber_dupbv_x(uid, &a->a_vals[0], op->o_tmpmemctx);
		}
		be_entry_release_r(op, e);
		if (a)
			return 1;
	}
	return 0;
}
