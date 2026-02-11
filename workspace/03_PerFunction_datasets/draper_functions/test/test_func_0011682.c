vcalviewer_get_request_values(VCalViewer *vcalviewer, MimeInfo *mimeinfo, gboolean is_todo)
{
	VCalEvent *saved_event = NULL;
	const gchar *charset = procmime_mimeinfo_get_parameter(mimeinfo, "charset");
	const gchar *saveme =  procmime_mimeinfo_get_parameter(mimeinfo, "vcalsave");

	if (!vcalviewer->event)
		return;

	if (!charset)
		charset = CS_WINDOWS_1252;

	if (!strcasecmp(charset, CS_ISO_8859_1))
		charset = CS_WINDOWS_1252;


	saved_event = vcal_manager_load_event(vcalviewer->event->uid);
	if (saved_event && saved_event->sequence >= vcalviewer->event->sequence) {
		charset = CS_INTERNAL;
		saved_event->method = vcalviewer->event->method;
		vcalviewer_display_event(vcalviewer, saved_event);
		vcal_manager_free_event(saved_event);
		return;
	} else if (saved_event) {
		vcal_manager_free_event(saved_event);
	}


	if (!saveme || strcmp(saveme,"no"))
		vcal_manager_save_event(vcalviewer->event, FALSE);

	vcalviewer_display_event(vcalviewer, vcalviewer->event);
}
