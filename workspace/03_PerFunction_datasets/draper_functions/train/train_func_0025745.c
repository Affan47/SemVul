marshall_PFR (struct soap *soap, struct ns1__TPutRequestFileStatus *repfilep, struct dpm_put_filereq *pfr_entry)
{
	time_t current_time = time(0);
	char *p;
	char turl[CA_MAXSFNLEN+1];

	if ((repfilep->fileSize = soap_malloc (soap, sizeof(ULONG64))))
		*repfilep->fileSize =
		    (pfr_entry->actual_size == LLONG_MAX) ? 0 : pfr_entry->actual_size;
	if ((repfilep->SURL =
	    soap_strdup (soap, pfr_entry->to_surl)) == NULL)
		return (-1);
	if ((repfilep->remainingPinLifetime = soap_malloc (soap, sizeof(int))))
		*repfilep->remainingPinLifetime = (pfr_entry->lifetime == 0x7FFFFFFF) ?
		    -1 : (pfr_entry->lifetime > current_time) ?
		    pfr_entry->lifetime - current_time : 0;
	if ((repfilep->remainingFileLifetime = soap_malloc (soap, sizeof(int))))
		*repfilep->remainingFileLifetime = (pfr_entry->f_lifetime == 0x7FFFFFFF) ?
		    -1 : (pfr_entry->f_lifetime > current_time) ?
		    pfr_entry->f_lifetime - current_time : 0;
	repfilep->status->statusCode =
	    dpmstatus2statuscode (pfr_entry->status, 'P', 1, pfr_entry->status == DPM_DONE ?
	    pfr_entry->f_lifetime : pfr_entry->lifetime);
	if (*pfr_entry->errstring)
		repfilep->status->explanation = soap_strdup (soap, pfr_entry->errstring);
	if (*pfr_entry->pfn) {
		if (strcmp (pfr_entry->protocol, "rfio") == 0)
			p = strchr (pfr_entry->pfn, ':') + 1;
		else
			p = pfr_entry->pfn;
		sprintf (turl, "%s://%s/%s", pfr_entry->protocol, pfr_entry->server, p);
		repfilep->transferURL = soap_strdup (soap, turl);
	}
	return (0);
}
