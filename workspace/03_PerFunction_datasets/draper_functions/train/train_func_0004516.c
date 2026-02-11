end_propstat(void *userdata, void *pstat_v,
			 const ne_status *status,
			 const char *description)
{
    struct propstat *pstat = pstat_v;


    if (!status) return;


    if (status->klass != 2) {
	int n;

	for (n = 0; n < pstat->numprops; n++) {
	    ne_free(pstat->props[n].value);
	    pstat->props[n].value = NULL;
	}
    }


    pstat->status = *status;
    pstat->status.reason_phrase = ne_strdup(status->reason_phrase);
}
