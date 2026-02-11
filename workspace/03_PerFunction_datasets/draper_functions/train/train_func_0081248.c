LoadThemeStyle(const std::string& widgettype, const std::string& object) {
	PG_Theme* t = PG_Application::GetTheme();

	const std::string& s = t->FindString(widgettype, object, PG_PropStr::label);

	if(!s.empty()) {
		SetText(s);
	}

	t->GetAlignment(widgettype, object, PG_PropStr::alignment, my_alignment);

	PG_Widget::LoadThemeStyle(widgettype, object);
}
