config_rename_add( Operation *op, SlapReply *rs, CfEntryInfo *ce,
	int base, int rebase, int max, int use_ldif )
{
	CfEntryInfo *ce2, *ce3, *cetmp = NULL, *cerem = NULL;
	ConfigType etype = ce->ce_type;
	int count = 0, rc = 0;


	for (ce2 = ce->ce_sibs;ce2;ce2 = ce3) {
		if (ce2->ce_type != etype) {
			cerem = ce2;
			break;
		}
		ce3 = ce2->ce_sibs;
		ce2->ce_sibs = cetmp;
		cetmp = ce2;
		count++;
		if ( max && count >= max ) {
			cerem = ce3;
			break;
		}
	}


	if ( rebase ) {
		ce->ce_entry->e_private = NULL;
		rc = config_renumber_one( op, rs, ce->ce_parent, ce->ce_entry,
			base+BIGTMP, 0, use_ldif );
		ce->ce_entry->e_private = ce;
	}

	for (ce2=cetmp; ce2; ce2=ce3) {
		ce3 = ce2->ce_sibs;
		ce2->ce_sibs = cerem;
		cerem = ce2;
		if ( rc == 0 )
			rc = config_renumber_one( op, rs, ce2->ce_parent, ce2->ce_entry,
				count+base, 0, use_ldif );
		count--;
	}
	if ( rebase )
		rc = config_renumber_one( op, rs, ce->ce_parent, ce->ce_entry,
			base, 0, use_ldif );
	return rc;
}
