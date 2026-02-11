audioev_filename_browse_play_cb (GtkWidget* ,
				 gpointer data)
{
  GmPreferencesWindow* pw = NULL;

  g_return_if_fail (data != NULL);

  pw = gm_pw_get_pw (GTK_WIDGET (data));

  boost::shared_ptr<Ekiga::AudioOutputCore> audiooutput_core = pw->core->get<Ekiga::AudioOutputCore> ("audiooutput-core");

  gchar* file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pw->fsbutton));
  std::string file_name_string = file_name;
  audiooutput_core->play_file(file_name_string);

  g_free (file_name);
}
