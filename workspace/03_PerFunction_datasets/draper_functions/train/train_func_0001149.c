update_softlimit(gfarm_time_t *exceedp, gfarm_time_t now, gfarm_time_t grace,
		gfarm_int64_t val, gfarm_int64_t soft)
{
	if (!quota_limit_is_valid(grace)  ||
	    !quota_limit_is_valid(soft)  ||
	    val <= soft
		) {
		*exceedp = GFARM_QUOTA_INVALID;
		return;
	} else if (*exceedp >= 0)
		return;
	else if (val > soft)
		*exceedp = now;
}
