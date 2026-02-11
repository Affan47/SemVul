lbtf_remove_card(struct lbtf_private *priv)
{
	struct ieee80211_hw *hw = priv->hw;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	priv->surpriseremoved = 1;
	del_timer(&priv->command_timer);
	lbtf_free_adapter(priv);
	priv->hw = NULL;
	ieee80211_unregister_hw(hw);
	ieee80211_free_hw(hw);

    lbtf_deb_leave(LBTF_DEB_MAIN);
	return 0;
}
