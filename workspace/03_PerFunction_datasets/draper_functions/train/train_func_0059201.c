parse_attributes(chunk_t chunk, int level0,
							 private_pkcs7_attributes_t* this)
{
	asn1_parser_t *parser;
	chunk_t object;
	int objectID;
	int oid = OID_UNKNOWN;
	bool success = FALSE;

	parser = asn1_parser_create(attributesObjects, chunk);
	parser->set_top_level(parser, level0);

	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)
		{
			case ATTRIBUTE_OBJ_TYPE:
				oid = asn1_known_oid(object);
				break;
			case ATTRIBUTE_OBJ_VALUE:
				if (oid != OID_UNKNOWN)
				{
					this->attributes->insert_last(this->attributes,
												  attribute_create(oid, object));
				}
				break;
		}
	}
	success = parser->success(parser);

	parser->destroy(parser);
	return success;
}
