info_window(const std::string& info)
{
			Gtk::MessageDialog dialog("Info",false,
					Gtk::MESSAGE_INFO);
			dialog.set_secondary_text(info);
			dialog.run();
}
