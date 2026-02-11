operator_error(int error_type)
{
	if (sms_redirect())
		popup_an_error("Keyboard locked");
	if (appres.oerr_lock || sms_redirect()) {
		status_oerr(error_type);
		mcursor_locked();
		kybdlock_set((unsigned int)error_type, "operator_error");
		(void) flush_ta();
	} else {
		ring_bell();
	}
}
