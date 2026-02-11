ath10k_tm_cmd_utf_stop(struct ath10k *ar, struct nlattr *tb[])
{
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode cmd utf stop\n");

	mutex_lock(&ar->conf_mutex);

	if (ar->state != ATH10K_STATE_UTF) {
		ret = -ENETDOWN;
		goto out;
	}

	__ath10k_tm_cmd_utf_stop(ar);

	ret = 0;

	ath10k_info(ar, "UTF firmware stopped\n");

out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}
