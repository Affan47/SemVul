GetPath() const
{
#if defined(__WXGTK24__) && (!defined(__WXGPE__))
   if (!gtk_check_version(2,4,0)) {
      char *f = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(m_widget));
      wxString path = wxConvFileName->cMB2WX(f);
      g_free(f);
      return path;
   }
   else
#endif
      return wxGenericFileDialog::GetPath();
}
