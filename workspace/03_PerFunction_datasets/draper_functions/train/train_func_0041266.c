operator=(const Style &source) {
	if (this == &source)
		return * this;
	Clear(ColourDesired(0, 0, 0), ColourDesired(0xff, 0xff, 0xff),
	      0, 0, SC_CHARSET_DEFAULT,
	      SC_WEIGHT_NORMAL, false, false, false, caseMixed, true, true, false);
	fore = source.fore;
	back = source.back;
	characterSet = source.characterSet;
	weight = source.weight;
	italic = source.italic;
	size = source.size;
	eolFilled = source.eolFilled;
	underline = source.underline;
	caseForce = source.caseForce;
	visible = source.visible;
	changeable = source.changeable;
	return *this;
}
