on_drog_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
		int, int, const Gtk::SelectionData& selection_data,
		guint,guint f_time)
{
	if((selection_data.get_length() >= 0)&&(selection_data.get_format()== 8))
	{
		context->drag_finish(false,false,f_time);
		std::string filename = wind_unescape_string(selection_data.get_text().c_str(), NULL);
		size_t pos = filename.find('\r');
		if (std::string::npos != pos)
			filename = filename.substr(7, pos-7);
		parent.open_file(filename);

	}
}
