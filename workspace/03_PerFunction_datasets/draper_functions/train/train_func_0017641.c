NP_GetValue (G_GNUC_UNUSED void *future, NPPVariable variable, void *value)
{
	switch (variable) {
	case NPPVpluginNameString:
		*((char **) value) = "Gnome Chemistry Utils";
		break;
	case NPPVpluginDescriptionString:
		*((char **) value) =
			"Gnome Chemistry Utils "VERSION". "
			"Chemical structures display.";
		break;
	default:
		return NPERR_GENERIC_ERROR;
	}
	return NPERR_NO_ERROR;
}
