checklacecount (bool lace)
{
	if (!interlace_changed) {
		if (nlace_cnt >= NLACE_CNT_NEEDED && lace) {
			lof_togglecnt_lace = LOF_TOGGLES_NEEDED;
			lof_togglecnt_nlace = 0;

			nlace_cnt = 0;
		} else if (nlace_cnt <= -NLACE_CNT_NEEDED && !lace) {
			lof_togglecnt_nlace = LOF_TOGGLES_NEEDED;
			lof_togglecnt_lace = 0;

			nlace_cnt = 0;
		}
	}
	if (lace) {
		if (nlace_cnt > 0)
			nlace_cnt = 0;
		nlace_cnt--;
		if (nlace_cnt < -NLACE_CNT_NEEDED * 2)
			nlace_cnt = -NLACE_CNT_NEEDED * 2;
	} else if (!lace) {
		if (nlace_cnt < 0)
			nlace_cnt = 0;
		nlace_cnt++;
		if (nlace_cnt > NLACE_CNT_NEEDED * 2)
			nlace_cnt = NLACE_CNT_NEEDED * 2;
	}
}
