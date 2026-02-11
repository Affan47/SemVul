on_menu_pop_copy_to_clipboard()
{
	Channel* channel = get_cur_select_channel();
	if (!channel)
		return;
	Glib::ustring stream = channel->get_stream();
	if (stream.empty())
		return;
	Glib::RefPtr<Gtk::Clipboard> clip = Gtk::Clipboard::get();
	clip->set_text(stream);
}
