shearwater_common_parser_create (dc_parser_t **out, dc_context_t *context, unsigned int petrel)
{
	if (out == NULL)
		return DC_STATUS_INVALIDARGS;


	shearwater_predator_parser_t *parser = (shearwater_predator_parser_t *) malloc (sizeof (shearwater_predator_parser_t));
	if (parser == NULL) {
		ERROR (context, "Failed to allocate memory.");
		return DC_STATUS_NOMEMORY;
	}


	parser->petrel = petrel;
	if (petrel) {
		parser_init (&parser->base, context, &shearwater_predator_parser_vtable);
	} else {
		parser_init (&parser->base, context, &shearwater_predator_parser_vtable);
	}

	*out = (dc_parser_t *) parser;

	return DC_STATUS_SUCCESS;
}
