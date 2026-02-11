SetLineEditAtts(PG_LineEdit *Widget, const char **atts, ParseUserData_t *XMLParser) {
	char	*c;

	if (PG_Layout::GetParamInt(atts, "readonly") == 1)
		Widget->SetEditable(0);

	c = PG_Layout::GetParamStr(atts, "validkeys");
	if (c[0] != 0)
		Widget->SetValidKeys(c);

	c = PG_Layout::GetParamStr(atts, "passchar");
	if (c[0] != 0)
		Widget->SetPassHidden(c[0]);

	return SetThemeWidgetAtts(Widget, atts, XMLParser);
}
