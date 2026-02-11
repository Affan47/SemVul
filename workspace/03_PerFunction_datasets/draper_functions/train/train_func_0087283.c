write_file_tpc(struct file *file, const char __user *user_buf,
			      size_t count, loff_t *ppos)
{
	struct ath_softc *sc = file->private_data;
	struct ath_hw *ah = sc->sc_ah;
	unsigned long val;
	char buf[32];
	ssize_t len;
	bool tpc_enabled;

	len = min(count, sizeof(buf) - 1);
	if (copy_from_user(buf, user_buf, len))
		return -EFAULT;

	buf[len] = '\0';
	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	if (val < 0 || val > 1)
		return -EINVAL;

	tpc_enabled = !!val;

	if (tpc_enabled != ah->tpc_enabled) {
		ah->tpc_enabled = tpc_enabled;

		mutex_lock(&sc->mutex);
		ath9k_set_txpower(sc, NULL);
		mutex_unlock(&sc->mutex);
	}

	return count;
}
