expat_XML_SetCharacterDataHandler(value parser, value handler)
{
    CAMLparam2(parser, handler);
    CAMLreturn (set_character_data_handler(parser, character_data_handler,
					   handler));
}
