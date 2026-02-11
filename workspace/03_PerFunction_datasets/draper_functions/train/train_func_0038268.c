mask_to_verbs(slap_verbmasks *v, slap_mask_t m, BerVarray *bva) {
	int i, rc = 1;

	if (m) {
		for (i=0; !BER_BVISNULL(&v[i].word); i++) {
			if (!v[i].mask) continue;
			if (( m & v[i].mask ) == v[i].mask ) {
				value_add_one( bva, &v[i].word );
				rc = 0;
				m ^= v[i].mask;
				if ( !m ) break;
			}
		}
	}
	return rc;
}
