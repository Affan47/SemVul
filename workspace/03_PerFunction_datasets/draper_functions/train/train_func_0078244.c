parse_digest_info(chunk_t blob, int level0, hash_algorithm_t *hash,
							  chunk_t *digest)
{
	asn1_parser_t *parser;
	chunk_t object;
	int objectID;
	bool success;

	parser = asn1_parser_create(digestInfoObjects, blob);
	parser->set_top_level(parser, level0);

	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)

		{
			case DIGEST_INFO_ALGORITHM:
			{
				int oid = asn1_parse_algorithmIdentifier(object,
									 parser->get_level(parser)+1, NULL);

				*hash = hasher_algorithm_from_oid(oid);
				break;
			}
			case DIGEST_INFO_DIGEST:
			{
				*digest = object;
				break;
			}
			default:
				break;
		}
	}
	success = parser->success(parser);
	parser->destroy(parser);
	return success;
}
