glcpp_parser_create (const struct gl_extensions *extensions, int api)
{
	glcpp_parser_t *parser;
	int language_version;

	parser = ralloc (NULL, glcpp_parser_t);

	glcpp_lex_init_extra (parser, &parser->scanner);
	parser->defines = hash_table_ctor (32, hash_table_string_hash,
					   hash_table_string_compare);
	parser->active = NULL;
	parser->lexing_if = 0;
	parser->space_tokens = 1;
	parser->newline_as_space = 0;
	parser->in_control_line = 0;
	parser->paren_count = 0;

	parser->skip_stack = NULL;

	parser->lex_from_list = NULL;
	parser->lex_from_node = NULL;

	parser->output = ralloc_strdup(parser, "");
	parser->info_log = ralloc_strdup(parser, "");
	parser->error = 0;


	add_builtin_define(parser, "GL_ARB_draw_buffers", 1);
	add_builtin_define(parser, "GL_ARB_texture_rectangle", 1);

	if (api == API_OPENGLES2)
		add_builtin_define(parser, "GL_ES", 1);

	if (extensions != NULL) {
	   if (extensions->EXT_texture_array) {
	      add_builtin_define(parser, "GL_EXT_texture_array", 1);
	   }

	   if (extensions->ARB_fragment_coord_conventions)
	      add_builtin_define(parser, "GL_ARB_fragment_coord_conventions",
				 1);

	   if (extensions->ARB_explicit_attrib_location)
	      add_builtin_define(parser, "GL_ARB_explicit_attrib_location", 1);
	   if (extensions->AMD_conservative_depth)
	      add_builtin_define(parser, "GL_AMD_conservative_depth", 1);
	}

	language_version = 110;
	add_builtin_define(parser, "__VERSION__", language_version);

	return parser;
}
