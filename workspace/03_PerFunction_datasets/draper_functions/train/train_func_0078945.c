show_textview_engine_log(const std::string& f_text)
{

	text_engine_log->set_wrap_mode(Gtk::WRAP_WORD);
	Glib::RefPtr<Gtk::TextBuffer> buffer_ = text_engine_log->get_buffer();
	Gtk::TextBuffer::iterator end_ = buffer_->end();

	Gdk::Rectangle rect_;
	text_engine_log->get_visible_rect(rect_);

	int y=-1;
	int height = -1;
	text_engine_log->get_line_yrange(end_,y,height);

	buffer_->place_cursor(buffer_->insert(end_,f_text));

	if(y<rect_.get_y() + rect_.get_height()+16)
		text_engine_log->scroll_to_mark(buffer_->get_insert(),0);
}
