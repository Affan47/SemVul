marshall_CPR (struct soap *soap, struct ns1__TCopyRequestFileStatus *repfilep, struct dpm_copy_filereq *cpr_entry)
{
	time_t current_time = time(0);

	if ((repfilep->fileSize = soap_malloc (soap, sizeof(ULONG64))))
		*repfilep->fileSize = cpr_entry->actual_size;
	if ((repfilep->sourceSURL =
	    soap_strdup (soap, cpr_entry->from_surl)) == NULL)
		return (-1);
	if ((repfilep->remainingFileLifetime = soap_malloc (soap, sizeof(int))))
		*repfilep->remainingFileLifetime = (cpr_entry->f_lifetime == 0x7FFFFFFF) ?
		    -1 : (cpr_entry->f_lifetime > current_time) ?
		    cpr_entry->f_lifetime - current_time : 0;
	repfilep->status->statusCode =
	    dpmstatus2statuscode (cpr_entry->status, 'C', 1, cpr_entry->f_lifetime);
	if (*cpr_entry->errstring)
		repfilep->status->explanation = soap_strdup (soap, cpr_entry->errstring);
	if ((repfilep->targetSURL =
	    soap_strdup (soap, cpr_entry->to_surl)) == NULL)
		return (-1);
	return (0);
}
