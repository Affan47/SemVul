on_loadimage_clicked
#endif
(GtkButton       *button, gpointer         user_data)
{

  int i = GPOINTER_TO_UINT(gtk_widget_get_data_top(GTK_WIDGET(button),"imagenum"));

#ifdef IS_PLYMORPH
  fileselection_hook=load_ply_from_file;
#else
  fileselection_hook=load_image_from_file;
#endif
  fileselection1_for_image_num_g=i;
  show_fs(
	  _("load %s")
#if GTK_MAJOR_VERSION >= 2
	     ,	    GTK_FILE_CHOOSER_ACTION_OPEN
#endif
	     );

  if (sp->im_filename_in[i] != NULL)
    gtk_file_selection_set_filename ((fileselection_g),
				     sp->im_filename_in[i] );
  else {
    if(i==MAIN_WIN) i=0;
    gtk_file_selection_set_filename ((fileselection_g),
#ifdef IS_PLYMORPH
				     g_strdup_printf("image%d.ply",i)
#else
				     g_strdup_printf("image%d.png",i)
#endif
				     );
  }
}
