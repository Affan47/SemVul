on_motion_event(GdkEventMotion * ev)
{
	Gtk::TreeModel::Path path;
	Gtk::TreeViewColumn * column;
	int cell_x, cell_y;
	int delay = 600;

	if (tipTimeout.connected()) {
		tipTimeout.disconnect();
	}
	if (this->
			get_path_at_pos((int) ev->x, (int) ev->y, path, column, cell_x,
				cell_y)) {
		Gtk::TreeModel::iterator iter =
			this->get_model()->get_iter(path);
		TypeChannel type = (*iter)[columns.type];
		if (GROUP_CHANNEL != type)
			tipTimeout =
				Glib::signal_timeout().connect(sigc::bind <
						GdkEventMotion *
						>(sigc::
							mem_fun(*this,
								&Channel::
								tooltip_timeout),
							ev), delay);
		else
			tooltips->hideTooltip();
	} else
		tooltips->hideTooltip();

	return true;
}
