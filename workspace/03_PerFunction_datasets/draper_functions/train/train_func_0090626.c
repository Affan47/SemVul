on_menu_hide_toolbar()
{


	Glib::RefPtr<Gtk::ToggleAction> show =
		Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(action_group->get_action("ViewShowToolbar"));

	if (show->get_active()){
		set_toolbar_hide(true);


	} else {
		set_toolbar_hide(false);


	}
	this->resize(1, 1);
}
