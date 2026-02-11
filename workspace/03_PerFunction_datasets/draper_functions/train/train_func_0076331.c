A_DeleteSMSMessage(gpointer data)
{
	gn_sms *sms = (gn_sms *) data;
	gn_error error = GN_ERR_UNKNOWN;
	gn_data gdat;

	gn_data_clear(&gdat);

	if (sms) {
		gdat.sms = sms;
		if (phoneMonitor.supported & PM_FOLDERS)
			error = gn_sms_delete_no_validate(&gdat, statemachine);
		else
			error = gn_sms_delete(&gdat, statemachine);
		g_free(sms);
	}
	return (error);
}
