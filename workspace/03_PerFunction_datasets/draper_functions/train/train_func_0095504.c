templates_get_template_licence(GeanyDocument *doc, gint licence_type)
{
	GString *template;

	g_return_val_if_fail(doc != NULL, NULL);
	g_return_val_if_fail(licence_type == GEANY_TEMPLATE_GPL || licence_type == GEANY_TEMPLATE_BSD, NULL);

	template = g_string_new(templates[licence_type]);
	replace_static_values(template);
	templates_replace_default_dates(template);
	templates_replace_command(template, DOC_FILENAME(doc), doc->file_type->name, NULL);

	make_comment_block(template, doc->file_type->id, GEANY_TEMPLATES_INDENT);
	convert_eol_characters(template, doc);

	return g_string_free(template, FALSE);
}
