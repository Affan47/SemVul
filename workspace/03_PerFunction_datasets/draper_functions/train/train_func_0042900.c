sidebar_finalize(void)
{
	if (WIDGET(tv.default_tag_tree))
	{
		gtk_widget_destroy(tv.default_tag_tree);
		g_object_unref(tv.default_tag_tree);
	}
	if (WIDGET(tv.popup_taglist))
		gtk_widget_destroy(tv.popup_taglist);
	if (WIDGET(openfiles_popup_menu))
		gtk_widget_destroy(openfiles_popup_menu);
}
