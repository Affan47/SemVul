Dialog_TextObject(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Dialog(cobject),
  m_box_title(0),
  m_entry_title(0),
  m_text_view(0)
{
  builder->get_widget("vbox_title",  m_box_title);
  builder->get_widget("entry_title",  m_entry_title);
  builder->get_widget("textview_text",  m_text_view);


  show_all_children();
}
