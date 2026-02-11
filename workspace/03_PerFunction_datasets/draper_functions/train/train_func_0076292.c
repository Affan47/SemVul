get() {
	Aeskulap::WindowLevel level;
	level.description = m_description->get_text();
	level.modality = m_modality->get_text();
	level.center = m_center->get_value_as_int();
	level.width = m_width->get_value_as_int();

	return level;
}
