il_chswitch_done(struct il_priv *il, bool is_success)
{
	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	if (test_and_clear_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		ieee80211_chswitch_done(il->vif, is_success);
}
