st_ll_wakeup(struct st_data_s *ll)
{
	if (likely(ll->ll_state != ST_LL_AWAKE)) {
		send_ll_cmd(ll, LL_WAKE_UP_IND);
		ll->ll_state = ST_LL_ASLEEP_TO_AWAKE;
	} else {

		pr_err(" Chip already AWAKE ");
	}
}
