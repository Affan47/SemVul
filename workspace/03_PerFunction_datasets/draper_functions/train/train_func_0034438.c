snic_dr_req_init(struct snic *snic, struct snic_req_info *rqi)
{
	struct snic_host_req *req = NULL;

	SNIC_BUG_ON(!rqi);

	req = mempool_alloc(snic->req_pool[SNIC_REQ_TM_CACHE], GFP_ATOMIC);
	if (!req) {
		SNIC_HOST_ERR(snic->shost, "dr:Failed to alloc tm req.\n");
		WARN_ON_ONCE(1);

		return NULL;
	}

	SNIC_BUG_ON(rqi->dr_req != NULL);
	rqi->dr_req = req;
	memset(req, 0, sizeof(struct snic_host_req));

	req->hdr.init_ctx = (ulong) rqi;

	return req;
}
