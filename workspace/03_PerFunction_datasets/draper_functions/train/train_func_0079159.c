rtl92ee_dm_write_dynamic_cca(struct ieee80211_hw *hw,
					 u8 cur_mf_state)
{
	struct dynamic_primary_cca *primarycca = &rtl_priv(hw)->primarycca;

	if (primarycca->mf_state != cur_mf_state)
		rtl_set_bbreg(hw, DM_REG_L1SBD_PD_CH_11N, BIT(8) | BIT(7),
			      cur_mf_state);

	primarycca->mf_state = cur_mf_state;
}
