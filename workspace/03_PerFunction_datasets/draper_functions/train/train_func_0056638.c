on_dialog_open(int response_id)
{
  Gtk::FileChooserDialog* dialog = NULL;
  m_refGlade->get_widget("dialog_open", dialog);
  if(dialog)
  {

    if(response_id == 1)
    {
      Glib::ustring file = Glib::filename_to_utf8(dialog->get_filename());

      if(Utils::Io::check_directory(file))
      {
        dialog->set_current_folder(file);
      }
      else if(file != "" && Utils::Io::check_file(file))
      {
        dialog->hide();
        m_pConfig->reset_to_defaults();
        if(ConfigLoader::load_config(file, m_pConfig, m_refGlade, this))
        {
          ModWidget::reload_all_widgets();
          m_filename = file;
        }
        else
          cout << "Couldn't load gnomecc theme!" << endl;
      }
    }
    else
      dialog->hide();

  }
}
