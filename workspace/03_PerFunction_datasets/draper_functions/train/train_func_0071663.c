refresh_purge( Operation *op, SlapReply *rs )
{
	if ( rs->sr_type == REP_SEARCH ) {
		refresh_info *ri = op->o_callback->sc_private;
		dnlist **dn;
		int del = 1;


		for ( dn=&ri->ri_dns; *dn; dn = &(*dn)->next ) {
			if ( dn_match( &(*dn)->dn, &rs->sr_entry->e_nname )) {
				dnlist *dnext = (*dn)->next;
				op->o_tmpfree( *dn, op->o_tmpmemctx );
				*dn = dnext;
				del = 0;
				break;
			}
		}

		if ( del ) {
			Attribute *a;
			dnlist *dnl = dnl_alloc( op, &rs->sr_entry->e_nname );
			dnl->next = ri->ri_dels;
			ri->ri_dels = dnl;
			a = attr_find( rs->sr_entry->e_attrs, ad_queryId );

			dnl->delete = ( a->a_numvals == 1 );
		}
	}
	return 0;
}
