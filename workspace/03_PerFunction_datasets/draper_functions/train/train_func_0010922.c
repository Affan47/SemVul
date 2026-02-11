go_editor_add_page (GOEditor *editor, gpointer widget, char const *label)
{
	GOEditorPage *page;

	g_return_if_fail (editor != NULL);
	page = g_new0 (GOEditorPage, 1);

	page->widget = widget;
#ifdef GOFFICE_WITH_GTK
	if (editor->use_scrolled) {
		page->scrolled = g_object_ref (gtk_scrolled_window_new (NULL, NULL));
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (page->scrolled),
			                                   widget);
	} else
#endif
		page->scrolled = g_object_ref (widget);
	page->label = label;

	editor->pages = g_slist_prepend (editor->pages, page);
}
