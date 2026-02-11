parse_authenticated_safe(private_pkcs12_t *this, chunk_t blob)
{
	asn1_parser_t *parser;
	chunk_t object;
	int objectID;
	bool success = FALSE;

	parser = asn1_parser_create(authenticatedSafeObjects, blob);

	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)
		{
			case AUTHENTICATED_SAFE_DATA:
			{
				container_t *container;
				chunk_t data;

				container = lib->creds->create(lib->creds, CRED_CONTAINER,
										CONTAINER_PKCS7, BUILD_BLOB_ASN1_DER,
										object, BUILD_END);
				if (!container)
				{
					goto end;
				}
				switch (container->get_type(container))
				{
					case CONTAINER_PKCS7_DATA:
					case CONTAINER_PKCS7_ENCRYPTED_DATA:
					case CONTAINER_PKCS7_ENVELOPED_DATA:
						if (container->get_data(container, &data))
						{
							break;
						}

					default:
						container->destroy(container);
						goto end;
				}
				container->destroy(container);

				if (!parse_safe_contents(this, parser->get_level(parser)+1,
										 data))
				{
					chunk_free(&data);
					goto end;
				}
				chunk_free(&data);
				break;
			}
		}
	}
	success = parser->success(parser);
end:
	parser->destroy(parser);
	return success;
}
