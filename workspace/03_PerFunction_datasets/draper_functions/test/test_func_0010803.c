SetUserButtonAtts(PG_Button *Widget, const char **atts, ParseUserData_t *XMLParser) {
	char	*c,*c1,*c2;
	int i,j,k;
	int b;

	c = PG_Layout::GetParamStr(atts, "upimage");
	c1 = PG_Layout::GetParamStr(atts, "downimage");
	c2 = PG_Layout::GetParamStr(atts, "overimage");


	if (c[0] != 0) {
		b = PG_Layout::GetParamInt(atts, "colorkey");
		if(b != -1) {
			Widget->SetIcon(c, c1, c2, b);
		} else {
			Widget->SetIcon(c, c1, c2);
		}
	}

	i = PG_Layout::GetParamInt(atts, "toggle");
	Widget->SetToggle(i == 1);

	i = PG_Layout::GetParamInt(atts, "pressed");
	Widget->SetPressed(i == 1);

	c = PG_Layout::GetParamStr(atts, "shift");
	if (c[0] != 0) {
		sscanf(c,"%d",&i);
		Widget->SetShift(i);
	}

	c = PG_Layout::GetParamStr(atts, "border");
	if (c[0] != 0) {
		sscanf(c,"%d,%d,%d",&i,&j,&k);
		Widget->SetBorderSize(i,j,k);
	}

	c = PG_Layout::GetParamStr(atts, "transparency");
	if (c[0] != 0) {
		sscanf(c,"%d,%d,%d",&i,&j,&k);
		Widget->SetTransparency(i,j,k);
	}

	return(SetWidgetAtts(Widget, atts, XMLParser));
}
