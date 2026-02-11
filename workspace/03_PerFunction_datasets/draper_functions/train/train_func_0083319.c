gsql_content_set_stock (GSQLContent *content, const gchar *stock)
{
	GSQL_TRACE_FUNC;

	g_return_if_fail (GSQL_IS_CONTENT (content));
	g_return_if_fail (stock != NULL);

	if (content->private->stock)
		g_free ((gchar *) content->private->stock);

	gtk_image_set_from_stock (content->private->header_icon, stock,
							  GTK_ICON_SIZE_MENU);
	gtk_image_set_from_stock (content->private->menuitem_icon, stock,
							  GTK_ICON_SIZE_MENU);
	content->private->stock = g_strdup (stock);

}
