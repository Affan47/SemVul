parse_rsa_private_key(chunk_t blob)
{
	chunk_t n, e, d, p, q, exp1, exp2, coeff;
	asn1_parser_t *parser;
	chunk_t object;
	int objectID ;
	bool success = FALSE;

	parser = asn1_parser_create(privkeyObjects, blob);
	parser->set_flags(parser, FALSE, TRUE);

	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)
		{
			case PRIV_KEY_VERSION:
				if (object.len > 0 && *object.ptr != 0)
				{
					DBG1(DBG_ASN, "PKCS#1 private key format is not version 1");
					goto end;
				}
				break;
			case PRIV_KEY_MODULUS:
				n = object;
				break;
			case PRIV_KEY_PUB_EXP:
				e = object;
				break;
			case PRIV_KEY_PRIV_EXP:
				d = object;
				break;
			case PRIV_KEY_PRIME1:
				p = object;
				break;
			case PRIV_KEY_PRIME2:
				q = object;
				break;
			case PRIV_KEY_EXP1:
				exp1 = object;
				break;
			case PRIV_KEY_EXP2:
				exp2 = object;
				break;
			case PRIV_KEY_COEFF:
				coeff = object;
				break;
		}
	}
	success = parser->success(parser);

end:
	parser->destroy(parser);
	if (!success)
	{
		return NULL;
	}
	return lib->creds->create(lib->creds, CRED_PRIVATE_KEY, KEY_RSA,
			BUILD_RSA_MODULUS, n, BUILD_RSA_PUB_EXP, e, BUILD_RSA_PRIV_EXP, d,
			BUILD_RSA_PRIME1, p,  BUILD_RSA_PRIME2, q, BUILD_RSA_EXP1, exp1,
			BUILD_RSA_EXP2, exp2, BUILD_RSA_COEFF, coeff, BUILD_END);
}
