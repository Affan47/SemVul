LoadThemeStyle(const std::string& widgettype, const std::string& objectname) {

	PG_Theme* t = PG_Application::GetTheme();

	if(my_srfObject == NULL) {
		if(objectname != PG_PropStr::ThemeWidget) {
			PG_ThemeWidget::LoadThemeStyle(widgettype, PG_PropStr::ThemeWidget);
		}

		t->GetProperty(widgettype, objectname, PG_PropStr::simplebackground, _mid->simplebackground);
		t->GetProperty(widgettype, objectname, PG_PropStr::nocache, _mid->nocache);
		t->GetColor(widgettype, objectname, PG_PropStr::backgroundcolor, _mid->backgroundcolor);
	}

	const std::string& font = t->FindFontName(widgettype, objectname);
	int fontsize = t->FindFontSize(widgettype, objectname);
	PG_Font::Style fontstyle = t->FindFontStyle(widgettype, objectname);

	if(!font.empty()) {
		SetFontName(font);
	}

	if(fontsize > 0) {
		SetFontSize(fontsize);
	}

	if(fontstyle >= 0) {
		SetFontStyle(fontstyle);
	}

	SetBackground(t->FindSurface(widgettype, objectname, PG_PropStr::background));

	t->GetProperty(widgettype, objectname, PG_PropStr::blend, my_blendLevel);
	t->GetProperty(widgettype, objectname, PG_PropStr::bordersize, my_bordersize);
	t->GetProperty(widgettype, objectname, PG_PropStr::backmode, my_backgroundMode);

	PG_Gradient* g = t->FindGradient(widgettype, objectname, PG_PropStr::gradient);

	if(g) {
		SetGradient(*g);
	}

	Uint8 trans = GetTransparency();
	t->GetProperty(widgettype, objectname, PG_PropStr::transparency, trans);
	SetTransparency(trans);

	PG_Widget::LoadThemeStyle(widgettype, objectname);

	int w = Width();
	t->GetProperty(widgettype, objectname, PG_PropStr::width, w);
	int h = Height();
	t->GetProperty(widgettype, objectname, PG_PropStr::height, h);

	if((w != Width()) || (h != Height())) {
		SizeWidget(w, h);
	}
}
