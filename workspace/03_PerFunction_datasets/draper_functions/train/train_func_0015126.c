indi_get_type_from_string(const char *typestr)
{

	typestr +=3;

	if        (strncmp(typestr, "Text", 4) == 0) {
		return INDI_PROP_TEXT;
	} else if (strncmp(typestr, "Number", 6) == 0) {
		return INDI_PROP_NUMBER;
	} else if (strncmp(typestr, "Switch", 6) == 0) {
		return INDI_PROP_SWITCH;
	} else if (strncmp(typestr, "Light", 5) == 0) {
		return INDI_PROP_LIGHT;
	} else if (strncmp(typestr, "BLOB", 4) == 0) {
		return INDI_PROP_BLOB;
	}
	return INDI_PROP_UNKNOWN;
}
