on_save_session_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  fileselection_hook=save_session;
  fileselection1_for_image_num_g=MAIN_WIN;
  show_fs(
	  _("save session")
#if GTK_MAJOR_VERSION >= 2
	  , GTK_FILE_CHOOSER_ACTION_SAVE
#endif
	  );
  if(!session_name){
#if GLIB_MAJOR_VERSION == 1
    session_name=g_strdup_printf("gtkmorph.session");
#else
    GDate D;
    g_date_set_time (&D, time (NULL));
    session_name=g_strdup_printf("%d-%02d-%02d.session",
				 g_date_get_year (&D),g_date_get_month (&D),
				 g_date_get_day (&D));
#endif
  }
  gtk_file_selection_set_filename ((fileselection_g),session_name);
}
