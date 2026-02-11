SPF_request_prepare(SPF_request_t *sr)
{
	if (sr->use_helo)
		sr->cur_dom = sr->helo_dom;
	else
		sr->cur_dom = sr->env_from_dp;
	return SPF_E_SUCCESS;
}
