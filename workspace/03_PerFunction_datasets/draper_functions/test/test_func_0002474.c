ecdsa_read_pubkey(const uint8_t *pub_key, curve_point *pub)
{
	if (pub_key[0] == 0x04) {
		bn_read_be(pub_key + 1, &(pub->x));
		bn_read_be(pub_key + 33, &(pub->y));
		return ecdsa_validate_pubkey(pub);
	}
	if (pub_key[0] == 0x02 || pub_key[0] == 0x03) {
		bn_read_be(pub_key + 1, &(pub->x));
		uncompress_coords(pub_key[0], &(pub->x), &(pub->y));
		return ecdsa_validate_pubkey(pub);
	}

	return 0;
}
