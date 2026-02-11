setMisc(FontState newfont,
	FontState org)
{
	if (newfont == FONT_TOGGLE) {
		if (org == FONT_ON)
			return FONT_OFF;
		else if (org == FONT_OFF)
			return FONT_ON;
		else {
			LYXERR0("Font::setMisc: Need state"
				" FONT_ON or FONT_OFF to toggle. Setting to FONT_ON");
			return FONT_ON;
		}
	} else if (newfont == FONT_IGNORE)
		return org;
	else
		return newfont;
}
