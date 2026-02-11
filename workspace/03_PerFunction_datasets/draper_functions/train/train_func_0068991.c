n_tickle(xmmsv_t *val, void *userdata)
{
	GMedialib  *gml = (GMedialib *)userdata;
	char const *xerr;

	if (xmmsv_get_error(val, &xerr)) {
		gchar buffer[128];
		snprintf(buffer, 128, "ERROR: Couldn't jump to that song: %s", xerr);
		gml_set_statusbar_text(gml, buffer);
	} else {
		xmms2ctrl_play(connection);
		gml_set_statusbar_text(gml, "Ready.");
	}
	return FALSE;
}
