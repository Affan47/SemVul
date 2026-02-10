Dialog_ChooseUser(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Dialog(cobject),
  m_combo_name(0)
{
  builder->get_widget_derived("combo_user_name", m_combo_name);
}
