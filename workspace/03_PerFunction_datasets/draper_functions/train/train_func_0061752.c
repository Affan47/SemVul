parse_private_key(chunk_t blob)
{
	asn1_parser_t *parser;
	chunk_t object, params = chunk_empty;
	int objectID;
	private_key_t *key = NULL;
	key_type_t type = KEY_ANY;

	parser = asn1_parser_create(pkinfoObjects, blob);
	parser->set_flags(parser, FALSE, TRUE);

	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)
		{
			case PKINFO_PRIVATE_KEY_ALGORITHM:
			{
				int oid = asn1_parse_algorithmIdentifier(object,
									parser->get_level(parser) + 1, &params);

				switch (oid)
				{
					case OID_RSA_ENCRYPTION:
						type = KEY_RSA;
						break;
					case OID_EC_PUBLICKEY:
						type = KEY_ECDSA;
						break;
					default:

						goto end;
				}
				break;
			}
			case PKINFO_PRIVATE_KEY:
			{
				DBG2(DBG_ASN, "-- > --");
				if (params.ptr)
				{
					key = lib->creds->create(lib->creds, CRED_PRIVATE_KEY,
											 type, BUILD_BLOB_ALGID_PARAMS,
											 params, BUILD_BLOB_ASN1_DER,
											 object, BUILD_END);
				}
				else
				{
					key = lib->creds->create(lib->creds, CRED_PRIVATE_KEY,
											 type, BUILD_BLOB_ASN1_DER, object,
											 BUILD_END);
				}
				DBG2(DBG_ASN, "-- < --");
				break;
			}
		}
	}

end:
	parser->destroy(parser);
	return key;
}
