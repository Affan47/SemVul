load_list_pixbuf(void)
{
GdkPixbuf *pixbuf;
guint i;
GtkWidget *cellview;

	DB( g_print("\n[homebank] load_list_pixbuf\n") );

	cellview = gtk_cell_view_new ();


	pixbuf = gtk_widget_render_icon (cellview, GTK_STOCK_NEW, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_ADD] = pixbuf;


	pixbuf = gtk_widget_render_icon (cellview, HB_STOCK_OPE_AUTO, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_AUTO] = pixbuf;


	pixbuf = gtk_widget_render_icon (cellview, GTK_STOCK_EDIT, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_EDIT] = pixbuf;


	pixbuf = gtk_widget_render_icon (cellview, HB_STOCK_OPE_REMIND, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_REMIND] = pixbuf;


	pixbuf = gtk_widget_render_icon (cellview, HB_STOCK_OPE_VALID, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_VALID] = pixbuf;


	pixbuf = gtk_widget_render_icon (cellview, GTK_STOCK_DIALOG_WARNING, GTK_ICON_SIZE_MENU, NULL);

	GLOBALS->lst_pixbuf[LST_PIXBUF_WARNING] = pixbuf;

	GLOBALS->lst_pixbuf_maxwidth = 0;
	for(i=0;i<NUM_LST_PIXBUF;i++)
	{
		if( GLOBALS->lst_pixbuf[i] != NULL )
			GLOBALS->lst_pixbuf_maxwidth = MAX(GLOBALS->lst_pixbuf_maxwidth, gdk_pixbuf_get_width(GLOBALS->lst_pixbuf[i]) );

	}

	DB( g_print(" -> pixbuf list maxwidth: %d\n", GLOBALS->lst_pixbuf_maxwidth) );

  gtk_widget_destroy (cellview);

}
