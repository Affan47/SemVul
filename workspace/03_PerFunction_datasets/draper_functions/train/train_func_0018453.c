on_build_start(GObject *obj, gpointer user_data)
{
	guint i;

	foreach_document(i)
	{
		if (gprj_project_is_in_project(documents[i]->file_name))
			document_save_file(documents[i], FALSE);
	}
}
