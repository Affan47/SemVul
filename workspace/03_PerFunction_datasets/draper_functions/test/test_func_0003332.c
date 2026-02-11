mdb_entry_partsize(struct mdb_info *mdb, MDB_txn *txn, Entry *e,
	Ecount *eh)
{
	ber_len_t len;
	int i, nat = 0, nval = 0, nnval = 0;
	Attribute *a;

	len = 4*sizeof(int);
	for (a=e->e_attrs; a; a=a->a_next) {

		nat++;
		if (a->a_desc->ad_index >= MDB_MAXADS) {
			Debug( LDAP_DEBUG_ANY, "mdb_entry_partsize: too many AttributeDescriptions used\n",
				0, 0, 0 );
			return LDAP_OTHER;
		}
		if (!mdb->mi_adxs[a->a_desc->ad_index]) {
			int rc = mdb_ad_get(mdb, txn, a->a_desc);
			if (rc)
				return rc;
		}
		len += 2*sizeof(int);
		nval += a->a_numvals + 1;
		for (i=0; i<a->a_numvals; i++) {
			len += a->a_vals[i].bv_len + 1 + sizeof(int);
		}
		if (a->a_nvals != a->a_vals) {
			nval += a->a_numvals + 1;
			nnval++;
			for (i=0; i<a->a_numvals; i++) {
				len += a->a_nvals[i].bv_len + 1 + sizeof(int);;
			}
		}
	}

	len = (len + sizeof(ID)-1) & ~(sizeof(ID)-1);
	eh->len = len;
	eh->nattrs = nat;
	eh->nvals = nval;
	eh->offset = nat + nval - nnval;
	return 0;
}
