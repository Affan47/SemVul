HueButton(const Glib::ustring& title, Gtk::Window& parent):
	m_title(title), m_parent(parent), m_saturation(1.0), m_value(1.0)
{
	parent.signal_hide().connect(
		sigc::mem_fun(*this, &HueButton::on_parent_hide));
	set_hue(1.0);
}
