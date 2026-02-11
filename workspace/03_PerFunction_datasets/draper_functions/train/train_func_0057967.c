sec80211_detect_ie ( int is_rsn, u8 *start, u8 *end,
			 enum net80211_security_proto *secprot,
			 enum net80211_crypto_alg *crypt )
{
	enum net80211_security_proto sp;
	enum net80211_crypto_alg cr;
	struct descriptor_map *map;
	u8 *rsn = start;


	cr = ( is_rsn ? NET80211_CRYPT_CCMP : NET80211_CRYPT_TKIP );
	sp = NET80211_SECPROT_EAP;

	rsn += 2;
	rsn += 4;

	if ( rsn >= end )
		goto done;


	map = rsn_pick_desc ( &rsn, end, rsn_cipher_map,
			      table_start ( NET80211_CRYPTOS ),
			      table_end ( NET80211_CRYPTOS ) );
	if ( ! map )
		goto invalid_rsn;

	cr = map->net80211_type;

	if ( rsn >= end )
		goto done;


	map = rsn_pick_desc ( &rsn, end, rsn_akm_map,
			      table_start ( NET80211_HANDSHAKERS ),
			      table_end ( NET80211_HANDSHAKERS ) );
	if ( ! map )
		goto invalid_rsn;

	sp = map->net80211_type;

 done:
	DBG ( "RSN detect: OK, crypto type %d, secprot type %d\n", cr, sp );
	*secprot = sp;
	*crypt = cr;
	return 0;

 invalid_rsn:
	DBG ( "RSN detect: invalid RSN IE\n" );
	return -EINVAL;
}
