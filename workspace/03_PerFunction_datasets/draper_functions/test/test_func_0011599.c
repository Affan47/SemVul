ShowModal()
{
   if ( !m_buttonlabel.IsEmpty() )
   {
      GtkWidget *widget;
      wxString label = m_buttonlabel;

      label.Replace(wxT("&"), wxT("_"));

      widget = gtk_button_new_with_mnemonic(wxGTK_CONV(label));
      gtk_file_chooser_set_extra_widget(GTK_FILE_CHOOSER(m_widget), widget);
      g_signal_connect(G_OBJECT(widget), "clicked",
                       GTK_SIGNAL_FUNC(gtk_filedialog_extra_callback), (gpointer)this);
   }

#if defined(__WXGTK24__) && (!defined(__WXGPE__))
   if (!gtk_check_version(2,4,0))
      return wxDialog::ShowModal();
   else
#endif
      return wxGenericFileDialog::ShowModal();
}
