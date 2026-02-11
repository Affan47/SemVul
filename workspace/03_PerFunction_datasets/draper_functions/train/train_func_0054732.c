__ad_timer_to_ticks(u16 timer_type, u16 par)
{
	u16 retval = 0;

	switch (timer_type) {
	case AD_CURRENT_WHILE_TIMER:
		if (par)
			retval = (AD_SHORT_TIMEOUT_TIME*ad_ticks_per_sec);
		else
			retval = (AD_LONG_TIMEOUT_TIME*ad_ticks_per_sec);
		break;
	case AD_ACTOR_CHURN_TIMER:
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		break;
	case AD_PERIODIC_TIMER:
		retval = (par*ad_ticks_per_sec);
		break;
	case AD_PARTNER_CHURN_TIMER:
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		break;
	case AD_WAIT_WHILE_TIMER:
		retval = (AD_AGGREGATE_WAIT_TIME*ad_ticks_per_sec);
		break;
	}

	return retval;
}
