sci_io_request_copy_response(struct isci_request *ireq)
{
	void *resp_buf;
	u32 len;
	struct ssp_response_iu *ssp_response;
	struct isci_tmf *isci_tmf = isci_request_access_tmf(ireq);

	ssp_response = &ireq->ssp.rsp;

	resp_buf = &isci_tmf->resp.resp_iu;

	len = min_t(u32,
		    SSP_RESP_IU_MAX_SIZE,
		    be32_to_cpu(ssp_response->response_data_len));

	memcpy(resp_buf, ssp_response->resp_data, len);
}
