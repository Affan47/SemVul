gmpc_meta_text_view_select_file (GmpcMetaTextView * self)
{
#line 980 "gmpc-meta-text-view.c"
#define __GOB_FUNCTION__ "Gmpc:Meta:Text:View::select_file"
#line 428 "gmpc-meta-text-view.gob"
	g_return_if_fail (self != NULL);
#line 428 "gmpc-meta-text-view.gob"
	g_return_if_fail (GMPC_IS_META_TEXT_VIEW (self));
#line 986 "gmpc-meta-text-view.c"
{
#line 431 "gmpc-meta-text-view.gob"

        gchar *p;
		mpd_Song *song = mpd_songDup(self->_priv->song);
		MetaDataType type = self->_priv->type;
		GtkFileFilter *gff = gtk_file_filter_new();
		GtkWidget *fcd = gtk_file_chooser_dialog_new(_("Select File"),NULL,
					 GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
		gtk_file_filter_set_name(gff, _("Text Document"));
		gtk_file_filter_add_mime_type(gff, "text/plain");
		gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fcd), gff);
		gff = gtk_file_filter_new();
		gtk_file_filter_set_name(gff, _("All"));
		gtk_file_filter_add_pattern(gff, "*");
		gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fcd), gff);

        p = cfg_get_single_value_as_string(config, "MetaData", "text-file-chooser");
        if(p) {
            gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(fcd), p);
            g_free(p);
        }
		gtk_widget_show_all(fcd);
		switch(gtk_dialog_run(GTK_DIALOG(fcd)))
		{
			case GTK_RESPONSE_ACCEPT:
				{
					gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fcd));
                    MetaData *met = meta_data_new();
                    met->type = type;
                    met->plugin_name = "User set";
                    met->content_type = META_DATA_CONTENT_URI;
                    met->content = filename; met->size =-1;
					meta_data_set_cache(song, META_DATA_AVAILABLE, met);
                    cfg_set_single_value_as_string(config, "MetaData", "text-file-chooser", filename);
					gmpc_meta_watcher_data_changed(gmw, song, type, META_DATA_AVAILABLE, met);

                    meta_data_free(met);
                }
            default:
				break;
		}
		gtk_widget_destroy(fcd);
		mpd_freeSong(song);

	}}
