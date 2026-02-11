on_refresh(void)
{
	GeanyDocument *doc = document_get_current();

	g_return_if_fail(doc);
	g_return_if_fail(edit_window.sci);

	set_editor(&edit_window, doc->editor);
}
