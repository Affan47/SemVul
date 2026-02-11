spawn_resp_unpack(spawn_resp_t **resp_ptr, Buf buf)
{
	spawn_resp_t *resp = NULL;
	uint32_t temp32;
	int i;

	resp = xmalloc(sizeof(spawn_resp_t));

	safe_unpack32(&resp->seq, buf);
	safe_unpack32((uint32_t *)&resp->rc, buf);
	safe_unpack16((uint16_t *)&resp->pmi_port, buf);
	safe_unpackstr_xmalloc(&resp->jobid, &temp32, buf);
	safe_unpack32(&resp->error_cnt, buf);
	if (resp->error_cnt > 0) {
		resp->error_codes = xmalloc(resp->error_cnt * sizeof(int));
		for (i = 0; i < resp->error_cnt; i ++) {
			safe_unpack32((uint32_t *)&(resp->error_codes[i]), buf);
		}
	}
	*resp_ptr = resp;
	return SLURM_SUCCESS;

unpack_error:
	spawn_resp_free(resp);
	return SLURM_ERROR;
}
