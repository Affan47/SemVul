on_list_user_requested_details(const Gnome::Gda::Value& primary_key_value)
{


  Glib::signal_idle().connect(
    sigc::bind(
      sigc::mem_fun(*this, &Notebook_Data::on_idle_show_details),
      primary_key_value));
}
