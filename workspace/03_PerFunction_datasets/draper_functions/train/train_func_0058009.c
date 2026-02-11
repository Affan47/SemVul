dpm_build_recall_request(struct dpm_dbfd *dbfd, struct dpm_req *dpm_req, struct dpm_get_filereq *gfr_entry, void *nearline_info, int backend_type, struct dpm_backend_req *backend_req)
{
	if (backend_req->nbreqfiles == 0) {
		backend_req->r_ordinal = dpm_req->r_ordinal;
		strcpy (backend_req->r_token, dpm_req->r_token);
		backend_req->r_uid = dpm_req->r_uid;
		backend_req->r_gid = dpm_req->r_gid;
		strcpy (backend_req->client_dn, dpm_req->client_dn);
		strcpy (backend_req->groups, dpm_req->groups);
		strcpy (backend_req->clienthost, dpm_req->clienthost);
		backend_req->retrytime = dpm_req->retrytime;
		backend_req->lifetime = gfr_entry->lifetime;
		strcpy (backend_req->s_token, gfr_entry->s_token);
		backend_req->ret_policy = gfr_entry->ret_policy;
		backend_req->f_type = gfr_entry->f_type;
		backend_req->ctime = time (0);
		backend_req->status = DPM_QUEUED;
	}
	backend_req->nbreqfiles++;

#ifdef DICOM
	if (backend_type == DPM_DICOM_RECALL) {
		struct dpm_dicom_filereq dfr_entry;

		memset (&dfr_entry, 0, sizeof(dfr_entry));
		strcpy (dfr_entry.r_token, gfr_entry->r_token);
		dfr_entry.f_ordinal = backend_req->nbreqfiles - 1;
		strcpy (dfr_entry.surl, gfr_entry->from_surl);
		strcpy (dfr_entry.dicom_fn, nearline_info + 8);
		dfr_entry.status = DPM_QUEUED;
		if (dpm_insert_dfr_entry (dbfd, &dfr_entry) < 0)
			return (-1);
	} else
#endif
	{
		serrno = SEPROTONOTSUP;
		return (-1);
	}
	return (0);
}
