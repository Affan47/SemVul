handle_subject_public_key_rsa (GcrParser *self,
                               GcrParsed *parsed,
                               GBytes *key,
                               GNode *params)
{
	gint res = GCR_ERROR_FAILURE;
	GNode *asn = NULL;

	asn = egg_asn1x_create_and_decode (pk_asn1_tab, "RSAPublicKey", key);
	if (!asn)
		goto done;

	parsing_object (parsed, CKO_PUBLIC_KEY);
	parsed_ulong_attribute (parsed, CKA_KEY_TYPE, CKK_RSA);

	if (!parsed_asn1_number (parsed, asn, "modulus", CKA_MODULUS) ||
	    !parsed_asn1_number (parsed, asn, "publicExponent", CKA_PUBLIC_EXPONENT))
		goto done;

	res = SUCCESS;

done:
	egg_asn1x_destroy (asn);
	return res;
}
