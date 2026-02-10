add_button (int code, const gchar *hint, GtkSignalFunc cb, int show)
{
  barpixwid[code] = gtk_pixmap_new(barpix[code], barmask[code]);
  gtk_widget_show(barpixwid[code]);
  mainbarbut[code] = gtk_toolbar_append_item(GTK_TOOLBAR(mainbar), NULL, hint,
		  NULL, barpixwid[code], cb, NULL);
  if (show)
  	gtk_widget_show(mainbarbut[code]);
  else
  	gtk_widget_hide(mainbarbut[code]);
}
