drag_data_received(GtkWidget *widget,
                              GdkDragContext *drag_context,
                              gint x, gint y,
                              GtkSelectionData *data,
                              guint info,
                              guint event_time,
                              gpointer user_data)
{
  gchar 	filename[256], *c;
  gint		i;
  GtkWidget	*dialog;

    switch (info) {
	case URI_LIST: {

	    if ((c = strstr((gchar *) data->data, URI_IDENTIFIER)) == NULL) {
		dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                	                  	 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                  	 GTK_MESSAGE_ERROR,
	                                  	 GTK_BUTTONS_CLOSE,
	                                  	 "Cannot extract filename from uri '%s'",
       		                          	 filename);
 		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		break;
	    }
	    strncpy(filename,&(c[strlen(URI_IDENTIFIER)]),256);
	    for (i=0;i<strlen(filename);i++) if (filename[i] == '\n') filename[i] = '\0';
	    SetupNewTab(filename, 1.0, -1, -1, FALSE);
	    break;
	}
	case JPEG_DATA:
	case PNG_DATA: {
	    printf("Received drag-and-drop jpeg_data or png_data\n");
            GError *error = NULL;
            GdkPixbufLoader *loader = gdk_pixbuf_loader_new_with_mime_type(gdk_atom_name(data->type), &error);
            if (loader) {
            	error = NULL;
            	if (gdk_pixbuf_loader_write( loader, data->data, data->length, &error)) {
                    GdkPixbuf *pbuf = gdk_pixbuf_loader_get_pixbuf(loader);
                    if ( pbuf ) {
                        int width = gdk_pixbuf_get_width(pbuf);
                        int height = gdk_pixbuf_get_height(pbuf);
                        printf("Received image of size %d x %d\n", width, height);
                    }
                }
            }
	    break;
	}
	case APP_X_COLOR: {
	    printf("Received drag-and-drop app-x-color\n");
	    break;
	}
    }
    gtk_drag_finish (drag_context, TRUE, FALSE, event_time);
}
