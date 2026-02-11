set_sensitive_png_background()
{
	guchar color[3];
	gint numCol = get_background_color(color);
	GtkWidget *pngTrans = gtk_ui_manager_get_widget (manager, "/MenuGL/ScreenCapture/ScreenCapturePNGWithoutBackGround");
	GtkWidget *clipTrans = gtk_ui_manager_get_widget (manager, "/MenuGL/ScreenCapture/ScreenCaptureClipBoardWithoutBackground");
	gboolean sensitive = TRUE;

	if(numCol<0) sensitive = FALSE;
	if(GTK_IS_WIDGET(pngTrans)) gtk_widget_set_sensitive(pngTrans, sensitive);
	if(GTK_IS_WIDGET(clipTrans)) gtk_widget_set_sensitive(clipTrans, sensitive);
}
