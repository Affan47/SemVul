parse_groups(private_x509_ac_t *this, chunk_t encoded, int level0)
{
	ac_group_type_t type;
	group_t *group;
	asn1_parser_t *parser;
	chunk_t object;
	int objectID;
	bool success;

	parser = asn1_parser_create(ietfAttrSyntaxObjects, encoded);
	parser->set_top_level(parser, level0);
	while (parser->iterate(parser, &objectID, &object))
	{
		switch (objectID)
		{
			case IETF_ATTR_OCTETS:
				type = AC_GROUP_TYPE_OCTETS;
				break;
			case IETF_ATTR_OID:
				type = AC_GROUP_TYPE_OID;
				break;
			case IETF_ATTR_STRING:
				type = AC_GROUP_TYPE_STRING;
				break;
			default:
				continue;
		}
		INIT(group,
			.type = type,
			.value = chunk_clone(object),
		);
		this->groups->insert_last(this->groups, group);
	}
	success = parser->success(parser);
	parser->destroy(parser);

	return success;
}
