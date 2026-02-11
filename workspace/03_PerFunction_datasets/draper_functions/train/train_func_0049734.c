acf_retrieve_docs(struct ast_custom_function *acf)
{
#ifdef AST_XML_DOCS
	char *tmpxml;


	if (!ast_strlen_zero(acf->desc) || !ast_strlen_zero(acf->synopsis)) {
		return 0;
	}

	if (ast_string_field_init(acf, 128)) {
		return -1;
	}


	tmpxml = ast_xmldoc_build_synopsis("function", acf->name, ast_module_name(acf->mod));
	ast_string_field_set(acf, synopsis, tmpxml);
	ast_free(tmpxml);


	tmpxml = ast_xmldoc_build_description("function", acf->name, ast_module_name(acf->mod));
	ast_string_field_set(acf, desc, tmpxml);
	ast_free(tmpxml);


	tmpxml = ast_xmldoc_build_syntax("function", acf->name, ast_module_name(acf->mod));
	ast_string_field_set(acf, syntax, tmpxml);
	ast_free(tmpxml);


	tmpxml = ast_xmldoc_build_arguments("function", acf->name, ast_module_name(acf->mod));
	ast_string_field_set(acf, arguments, tmpxml);
	ast_free(tmpxml);


	tmpxml = ast_xmldoc_build_seealso("function", acf->name, ast_module_name(acf->mod));
	ast_string_field_set(acf, seealso, tmpxml);
	ast_free(tmpxml);

	acf->docsrc = AST_XML_DOC;
#endif

	return 0;
}
