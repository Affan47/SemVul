ColourOfProperty(PropSetFile *props, const char *key, ColourDesired colourDefault) {
	SString colour = props->Get(key);
	if (colour.length()) {
		return ColourFromString(colour.c_str()).AsLong();
	}
	return colourDefault.AsLong();
}
