unset_color ()
{
	if (is_force_needed ())
		unset_style ();
	else
	{
		unset_bg (Gtk::STATE_NORMAL);
		unset_bg (Gtk::STATE_ACTIVE);
		unset_bg (Gtk::STATE_PRELIGHT);
	}

	if (Gtk::Widget *child = get_child ())
		unset_fgcolor (*child);
}
