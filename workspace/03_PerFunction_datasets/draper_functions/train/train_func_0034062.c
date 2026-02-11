il3945_bg_restart(struct work_struct *data)
{
	struct il_priv *il = container_of(data, struct il_priv, restart);

	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	if (test_and_clear_bit(S_FW_ERROR, &il->status)) {
		mutex_lock(&il->mutex);
		il->is_open = 0;
		mutex_unlock(&il->mutex);
		il3945_down(il);
		ieee80211_restart_hw(il->hw);
	} else {
		il3945_down(il);

		mutex_lock(&il->mutex);
		if (test_bit(S_EXIT_PENDING, &il->status)) {
			mutex_unlock(&il->mutex);
			return;
		}

		__il3945_up(il);
		mutex_unlock(&il->mutex);
	}
}
