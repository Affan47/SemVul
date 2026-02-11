parse_public_key(private_pgp_cert_t *this, chunk_t packet)
{
	chunk_t pubkey_packet = packet;

	if (!pgp_read_scalar(&packet, 1, &this->version))
	{
		return FALSE;
	}
	switch (this->version)
	{
		case 3:
			if (!pgp_read_scalar(&packet, 4, &this->created) ||
				!pgp_read_scalar(&packet, 2, &this->valid))
			{
				return FALSE;
			}
			break;
		case 4:
			if (!pgp_read_scalar(&packet, 4, &this->created))
			{
				return FALSE;
			}
			break;
		default:
			DBG1(DBG_ASN, "PGP packet version V%d not supported",
				 this->version);
			return FALSE;
	}
	if (this->valid)
	{
		DBG2(DBG_ASN, "L2 - created %T, valid %d days", &this->created, FALSE,
			 this->valid);
	}
	else
	{
		DBG2(DBG_ASN, "L2 - created %T, never expires", &this->created, FALSE);
	}
	DESTROY_IF(this->key);
	this->key = lib->creds->create(lib->creds, CRED_PUBLIC_KEY, KEY_ANY,
									BUILD_BLOB_PGP, packet, BUILD_END);
	if (this->key == NULL)
	{
		return FALSE;
	}


	if (this->version == 4)
	{
		chunk_t pubkey_packet_header = chunk_from_chars(
					0x99, pubkey_packet.len / 256, pubkey_packet.len % 256
				);
		hasher_t *hasher;

		hasher = lib->crypto->create_hasher(lib->crypto, HASH_SHA1);
		if (hasher == NULL)
		{
			DBG1(DBG_ASN, "no SHA-1 hasher available");
			return FALSE;
		}
		if (!hasher->allocate_hash(hasher, pubkey_packet_header, NULL) ||
			!hasher->allocate_hash(hasher, pubkey_packet, &this->fingerprint))
		{
			hasher->destroy(hasher);
			return FALSE;
		}
		hasher->destroy(hasher);
		DBG2(DBG_ASN, "L2 - v4 fingerprint %#B", &this->fingerprint);
	}
	else
	{

		if (!this->key->get_fingerprint(this->key, KEYID_PGPV3,
										&this->fingerprint))
		{
			return FALSE;
		}
		this->fingerprint = chunk_clone(this->fingerprint);
		DBG2(DBG_ASN, "L2 - v3 fingerprint %#B", &this->fingerprint);
	}
	return TRUE;
}
