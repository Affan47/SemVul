set_visible (bool yn)
{


	if (own_window.is_visible()) {
		return;
	}

	if (_visible != yn) {
		_visible = yn;
		if (yn) {
			show_all();
			Visible ();
		} else {
			hide ();
			Hidden ();
		}
	}
}
