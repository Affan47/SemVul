cdxml_string_start (GsfXMLIn *xin, xmlChar const **attrs)
{
	CDXMLReadState	*state = (CDXMLReadState *) xin->user_state;
	state->attributes = 0;
	while (*attrs) {
		if (!strcmp ((char const *) *attrs, "font")) {
			attrs++;
			state->font = atoi ((char const *) *attrs);
			state->markup += "<font name=\"";
			state->markup += state->fonts[state->font].name;
			state->markup += " ";
		} else if (!strcmp ((char const *) *attrs, "face"))  {
			attrs++;
			state->attributes |= atoi ((char const *) *attrs);
		} else if (!strcmp ((char const *) *attrs, "size"))  {
			attrs++;
			state->size = (char const *) *attrs;
		} else if (!strcmp ((char const *) *attrs, "color"))  {
			attrs++;
			state->attributes |= 0x100;
			state->color = atoi ((char const *) *attrs);
		} else
			attrs ++;
		attrs++;
	}
	state->markup += string (" ") + state->size + "\">";
	if (state->attributes & 0x100)
		state->markup += string ("<fore ") + state->colors[state->color] + ">";
	if (state->attributes & 1)
		state->markup += "<b>";
	if (state->attributes & 2)
		state->markup += "<i>";
	if (state->attributes & 4)
		state->markup += "<u>";
	if ((state->attributes & 0x60) != 0x60) {
		if (state->attributes & 0x20)
			state->markup += "<sub>";
		else if (state->attributes & 0x40)
			state->markup += "<sup>";
	}


}
