glatex_init_cutom_template_item(gchar *file, GPtrArray *array)
{
	TemplateEntry *template = NULL;
	gchar *tmp = NULL;


	if (g_str_has_suffix(file,".gtl") == FALSE)
		return;

	template = g_new0(TemplateEntry, 1);

	template->filepath = g_strdup(file);

	tmp = g_path_get_basename(file);
	template->label = utils_remove_ext_from_filename(tmp);
	g_free(tmp);


	template->template = glatex_get_template_from_file(file);
	g_ptr_array_add(array, template);
}
