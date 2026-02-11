ExportToHtmlDialog(const std::string & default_file)
  : Gtk::FileChooserDialog(_("Destination for HTML Export"),
                           Gtk::FILE_CHOOSER_ACTION_SAVE)
  , m_export_linked(_("Export linked notes"))
  , m_export_linked_all(_("Include all other linked notes"))
{
  add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

  set_default_response(Gtk::RESPONSE_OK);

  Gtk::Table *table = manage(new Gtk::Table (2, 2, false));

  m_export_linked.signal_toggled().connect(
    sigc::mem_fun(*this, &ExportToHtmlDialog::on_export_linked_toggled));

  table->attach (m_export_linked, 0, 2, 0, 1, Gtk::FILL, (Gtk::AttachOptions)0, 0, 0);
  table->attach (m_export_linked_all,
                 1, 2, 1, 2, Gtk::EXPAND | Gtk::FILL, (Gtk::AttachOptions)0, 20, 0);

  set_extra_widget(*table);

  set_do_overwrite_confirmation(true);
  set_local_only(true);

  show_all ();
  load_preferences (default_file);
}
