LoadThemeStyle(const std::string& widgettype, const std::string& objectname) {
	PG_Theme* t = PG_Application::GetTheme();
	PG_Gradient* g = NULL;

	my_background[0] = t->FindSurface(widgettype, objectname, PG_PropStr::background0);
	my_background[1] = t->FindSurface(widgettype, objectname, PG_PropStr::background1);
	my_background[2] = t->FindSurface(widgettype, objectname, PG_PropStr::background2);

	t->GetProperty(widgettype, objectname, PG_PropStr::blend0, my_blend[0]);
	t->GetProperty(widgettype, objectname, PG_PropStr::blend1, my_blend[1]);
	t->GetProperty(widgettype, objectname, PG_PropStr::blend2, my_blend[2]);

	t->GetProperty(widgettype, objectname, PG_PropStr::backmode0, my_bkmode[0]);
	t->GetProperty(widgettype, objectname, PG_PropStr::backmode1, my_bkmode[1]);
	t->GetProperty(widgettype, objectname, PG_PropStr::backmode2, my_bkmode[2]);

	g = t->FindGradient(widgettype, objectname, PG_PropStr::gradient0);
	if(g)
		my_gradient[0] = g;
	g = t->FindGradient(widgettype, objectname, PG_PropStr::gradient1);
	if(g)
		my_gradient[1] = g;
	g = t->FindGradient(widgettype, objectname, PG_PropStr::gradient2);
	if(g)
		my_gradient[2] = g;

	PG_Color fontcolor(0xFFFFFF);
	t->GetColor(widgettype, objectname, PG_PropStr::textcolor, fontcolor);
	SetFontColor(fontcolor);
}
