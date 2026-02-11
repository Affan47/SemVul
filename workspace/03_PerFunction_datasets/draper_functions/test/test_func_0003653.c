_get_entity(void *user, const xmlChar *name)
{
	XML_Parser parser = (XML_Parser) user;
	xmlEntityPtr ret = NULL;

	if (parser->parser->inSubset == 0) {
		ret = xmlGetPredefinedEntity(name);
		if (ret == NULL)
			ret = xmlGetDocEntity(parser->parser->myDoc, name);

		if (ret == NULL || (parser->parser->instate != XML_PARSER_ENTITY_VALUE && parser->parser->instate != XML_PARSER_ATTRIBUTE_VALUE)) {
			if (ret == NULL || ret->etype == XML_INTERNAL_GENERAL_ENTITY || ret->etype == XML_INTERNAL_PARAMETER_ENTITY || ret->etype == XML_INTERNAL_PREDEFINED_ENTITY) {

				if (parser->h_default && ! (ret && ret->etype == XML_INTERNAL_PREDEFINED_ENTITY && parser->h_cdata)) {
					xmlChar *entity;
					int      len;

					_build_entity(name, xmlStrlen(name), &entity, &len);
					parser->h_default(parser->user, (const xmlChar *) entity, len);
					xmlFree(entity);
				} else {


					if (parser->h_cdata && ret) {
						parser->h_cdata(parser->user, ret->content, xmlStrlen(ret->content));
					}
				}
			} else {
				if (ret->etype == XML_EXTERNAL_GENERAL_PARSED_ENTITY) {
					_external_entity_ref_handler(user, ret->name, ret->etype, ret->SystemID, ret->ExternalID, NULL);
				}
			}
		}
	}

	return ret;
}
