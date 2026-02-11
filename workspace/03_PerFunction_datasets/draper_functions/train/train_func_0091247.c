NotebookGlom(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& )
: Gtk::Notebook(cobject)
{
#ifndef GLOM_ENABLE_CLIENT_ONLY
  setup_menu();
#endif

  init();


}
