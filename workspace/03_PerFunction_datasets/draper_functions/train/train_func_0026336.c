validation_barf (WorkbookControl *wbc, GnmValidation const *gv,
		 char *def_msg, gboolean *showed_dialog)
{
	char const *msg = gv->msg ? gv->msg->str : def_msg;
	char const *title = gv->title ? gv->title->str : _("Gnumeric: Validation");
	ValidationStatus result;

	if (gv->style == GNM_VALIDATION_STYLE_NONE) {

		result = GNM_VALIDATION_STATUS_VALID;
	} else {
		if (showed_dialog) *showed_dialog = TRUE;
		result = wb_control_validation_msg (wbc, gv->style, title, msg);
	}
	g_free (def_msg);
	return result;
}
