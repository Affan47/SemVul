A_SendSMSMessage(gpointer data)
{
	D_SMSMessage *d = (D_SMSMessage *) data;
	gn_error error = GN_ERR_UNKNOWN;
	gn_data gdat;

	if (!d)
		return error;

	gn_data_clear(&gdat);

	gdat.sms = d->sms;
	pthread_mutex_lock(&sendSMSMutex);
	error = d->status = gn_sms_send(&gdat, statemachine);

	free(gdat.sms->reference);
	pthread_cond_signal(&sendSMSCond);
	pthread_mutex_unlock(&sendSMSMutex);

	return (error);
}
