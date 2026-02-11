init ()
{
	set_type_hint (Gdk::WINDOW_TYPE_HINT_DIALOG);
	set_position (Gtk::WIN_POS_MOUSE);
	set_name ("Prompter");

	add_button (Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);


	entryLabel.set_line_wrap (true);
	entryLabel.set_name ("PrompterLabel");

	entryBox.set_homogeneous (false);
	entryBox.set_spacing (5);
	entryBox.set_border_width (10);
	entryBox.pack_start (entryLabel);
	entryBox.pack_start (entry, false, false);

	get_vbox()->pack_start (entryBox);
	show_all_children();
	entry.signal_changed().connect (mem_fun (*this, &Prompter::on_entry_changed));
	entry.signal_activate().connect (bind (mem_fun (*this, &Prompter::response), Gtk::RESPONSE_ACCEPT));
}
