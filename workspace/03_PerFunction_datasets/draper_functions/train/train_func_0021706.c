on_box_print_layouts_selected(const Glib::ustring& print_layout_name)
{

  if(!m_pDialogLayoutPrint)
  {
    Utils::get_glade_widget_derived_with_warning(m_pDialogLayoutPrint);
    if(!m_pDialogLayoutPrint)
    {
      std::cerr << G_STRFUNC << ": m_pDialogLayoutPrint is null" << std::endl;
      return;
    }

    add_view(m_pDialogLayoutPrint);
    m_pDialogLayoutPrint->signal_hide().connect( sigc::mem_fun(*this, &Frame_Glom::on_dialog_layout_print_hide) );
  }

  m_pDialog_PrintLayouts->hide();

  sharedptr<PrintLayout> print_layout = get_document()->get_print_layout(m_table_name, print_layout_name);
  if(print_layout)
  {
    Gtk::Window* app_window = get_app_window();
    if(app_window)
      m_pDialogLayoutPrint->set_transient_for(*app_window);

    m_pDialogLayoutPrint->set_print_layout(m_table_name, print_layout);
    m_pDialogLayoutPrint->show();
  }
}
