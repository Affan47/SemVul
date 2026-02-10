on_bfsok_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *filename;


  tanstatpop();
  filename=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filselwin));

  if (filselnr==FIGGC){
    if (tanloadfigtab(filename)){
      gchar *str;
      str = g_strdup_printf(_("%d figures loaded."),figtabsize);
      tanstatprov(str);
      g_free(str);
    }
    else{
      tanstatprov(_("Can't load figure file."));
    }
  }
  else{
    tansetpixmapmode(widgetgrande, filename, filselnr);
    if (filselnr<=GCPIECELAST)
      tanredrawgrande();
    else
      tanredrawpetite();
  }
  gtk_widget_hide (gtk_widget_get_toplevel (GTK_WIDGET (button)));
}
