set_information()
{
	Gtk::Label* info   = 0;ui_xml->get_widget("info_label",info);

	const Board_info& board_info = board->get_board_info();
	p1_name->set_label(board_info.black);
	p2_name->set_label(board_info.red);
	Glib::ustring text = Glib::ustring(_("Game: ")) +board_info.event+"\n";
	text = text + _("Time: ")+board_info.date+"\n";
	text = text + _("Site: ")+board_info.site+"\n";
	text = text + _("Result: ")+board_info.result+"\n";
	text = text + _("Opening: ")+board_info.opening+"\n";
	text = text + _("Variation:  ")+board_info.variation+"\n";
	info->set_label(text);
	info->set_ellipsize(Pango::ELLIPSIZE_END);
	set_status();

}
