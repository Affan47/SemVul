document_finalize()
{
	guint i;

	for (i = 0; i < documents_array->len; i++)
		g_free(documents[i]);
	g_ptr_array_free(documents_array, TRUE);
}
