attr_syntax_delete_no_lock( struct asyntaxinfo *asi,
		PRBool remove_from_oidtable )
{
	int		i;

	if (oid2asi && remove_from_oidtable ) {
		PL_HashTableRemove(oid2asi, asi->asi_oid);
	}

	if(name2asi) {
		PL_HashTableRemove(name2asi, asi->asi_name);
		if ( asi->asi_aliases != NULL ) {
			for ( i = 0; asi->asi_aliases[i] != NULL; ++i ) {
				PL_HashTableRemove(name2asi, asi->asi_aliases[i]);
			}
		}
		if ( asi->asi_refcnt > 0 ) {
			asi->asi_marked_for_delete = PR_TRUE;
		} else {


			attr_syntax_free(asi);
		}
	}
}
