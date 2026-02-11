setFont()
{
	gMainWindow *win = window();
	if (label) gtk_widget_modify_font(GTK_WIDGET(label), win->ownFont() ? win->font()->desc() : NULL);
	if (aclbl) gtk_widget_modify_font(GTK_WIDGET(aclbl), win->ownFont() ? win->font()->desc() : NULL);
}
