lpfc_bsg_mbox_cmd(struct fc_bsg_job *job)
{
	struct lpfc_vport *vport = (struct lpfc_vport *)job->shost->hostdata;
	struct lpfc_hba *phba = vport->phba;
	struct dfc_mbox_req *mbox_req;
	int rc = 0;


	job->reply->reply_payload_rcv_len = 0;
	if (job->request_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct dfc_mbox_req)) {
		lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2737 Mix-and-match backward compatibility "
				"between MBOX_REQ old size:%d and "
				"new request size:%d\n",
				(int)(job->request_len -
				      sizeof(struct fc_bsg_request)),
				(int)sizeof(struct dfc_mbox_req));
		mbox_req = (struct dfc_mbox_req *)
				job->request->rqst_data.h_vendor.vendor_cmd;
		mbox_req->extMboxTag = 0;
		mbox_req->extSeqNum = 0;
	}

	rc = lpfc_bsg_issue_mbox(phba, job, vport);

	if (rc == 0) {

		job->reply->result = 0;
		job->dd_data = NULL;
		job->job_done(job);
	} else if (rc == 1)

		rc = 0;
	else {

		job->reply->result = rc;
		job->dd_data = NULL;
	}

	return rc;
}
