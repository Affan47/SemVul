scep_parse_response(chunk_t response, chunk_t transID,
						  container_t **out, scep_attributes_t *attrs)
{
	enumerator_t *enumerator;
	bool verified = FALSE;
	container_t *container;
	auth_cfg_t *auth;

	container = lib->creds->create(lib->creds, CRED_CONTAINER, CONTAINER_PKCS7,
								   BUILD_BLOB_ASN1_DER, response, BUILD_END);
	if (!container)
	{
		return "error parsing the scep response";
	}
	if (container->get_type(container) != CONTAINER_PKCS7_SIGNED_DATA)
	{
		container->destroy(container);
		return "scep response is not PKCS#7 signed-data";
	}

	enumerator = container->create_signature_enumerator(container);
	while (enumerator->enumerate(enumerator, &auth))
	{
		verified = TRUE;
		extract_attributes((pkcs7_t*)container, enumerator, attrs);
		if (!chunk_equals(transID, attrs->transID))
		{
			enumerator->destroy(enumerator);
			container->destroy(container);
			return "transaction ID of scep response does not match";
		}
	}
	enumerator->destroy(enumerator);
	if (!verified)
	{
		container->destroy(container);
		return "unable to verify PKCS#7 container";
	}
	*out = container;
	return NULL;
}
