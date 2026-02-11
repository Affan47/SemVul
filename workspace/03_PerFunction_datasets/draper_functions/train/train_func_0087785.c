FloatWidget(Gtk::Widget& parent, int width, int height) :
m_width(width),
m_height(height) {
	m_parent = &parent;

	resize(m_width, m_height);
	set_decorated(false);
	set_keep_above();
	set_skip_taskbar_hint(true);
	set_skip_pager_hint(true);
	set_type_hint(Gdk::WINDOW_TYPE_HINT_UTILITY);
	reparent(parent);

	m_widgetlist.insert(this);
}
