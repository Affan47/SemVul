ath6kl_credit_reduce(struct ath6kl_htc_credit_info *cred_info,
				 struct htc_endpoint_credit_dist *ep_dist,
				 int limit)
{
	int credits;

	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit reduce ep %d limit %d\n",
		   ep_dist->endpoint, limit);

	ep_dist->cred_assngd = limit;

	if (ep_dist->credits <= limit)
		return;

	credits = ep_dist->credits - limit;
	ep_dist->credits -= credits;
	cred_info->cur_free_credits += credits;
}
