on_menu_events (wxCommandEvent &ev)
{
	if (ev.GetId() == ID_BindMenuOp) {
		bind_request();
	}
	else if (ev.GetId() == ID_EditMenuOp) {
		show_text_ctrl ();
	}
	else if (ev.GetId() == ID_DefaultMenuOp) {
		_value = max (min (_default_val, _upper_bound), _lower_bound);

		value_changed(get_value());
		update_value_str();
		Refresh(false);
	}
}
