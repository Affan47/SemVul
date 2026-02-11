__volume_set_mute_ec(const bool mute)
{
	int rc;
	u8 s, n;

	if (mutex_lock_killable(&volume_mutex) < 0)
		return -EINTR;

	rc = volume_get_status_ec(&s);
	if (rc)
		goto unlock;

	n = (mute) ? s | TP_EC_AUDIO_MUTESW_MSK :
		     s & ~TP_EC_AUDIO_MUTESW_MSK;

	if (n != s) {
		rc = volume_set_status_ec(n);
		if (!rc)
			rc = 1;
	}

unlock:
	mutex_unlock(&volume_mutex);
	return rc;
}
