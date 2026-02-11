ath5k_hw_set_opmode(struct ath5k_hw *ah, enum nl80211_iftype op_mode)
{
	struct ath_common *common = ath5k_hw_common(ah);
	u32 pcu_reg, beacon_reg, low_id, high_id;

	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "mode %d\n", op_mode);


	pcu_reg = ath5k_hw_reg_read(ah, AR5K_STA_ID1) & 0xffff0000;
	pcu_reg &= ~(AR5K_STA_ID1_ADHOC | AR5K_STA_ID1_AP
			| AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
			(AR5K_STA_ID1_PWR_SV | AR5K_STA_ID1_NO_PSPOLL) : 0));

	beacon_reg = 0;

	switch (op_mode) {
	case NL80211_IFTYPE_ADHOC:
		pcu_reg |= AR5K_STA_ID1_ADHOC | AR5K_STA_ID1_KEYSRCH_MODE;
		beacon_reg |= AR5K_BCR_ADHOC;
		if (ah->ah_version == AR5K_AR5210)
			pcu_reg |= AR5K_STA_ID1_NO_PSPOLL;
		else
			AR5K_REG_ENABLE_BITS(ah, AR5K_CFG, AR5K_CFG_IBSS);
		break;

	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		pcu_reg |= AR5K_STA_ID1_AP | AR5K_STA_ID1_KEYSRCH_MODE;
		beacon_reg |= AR5K_BCR_AP;
		if (ah->ah_version == AR5K_AR5210)
			pcu_reg |= AR5K_STA_ID1_NO_PSPOLL;
		else
			AR5K_REG_DISABLE_BITS(ah, AR5K_CFG, AR5K_CFG_IBSS);
		break;

	case NL80211_IFTYPE_STATION:
		pcu_reg |= AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
				AR5K_STA_ID1_PWR_SV : 0);

	case NL80211_IFTYPE_MONITOR:
		pcu_reg |= AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
				AR5K_STA_ID1_NO_PSPOLL : 0);
		break;

	default:
		return -EINVAL;
	}


	low_id = get_unaligned_le32(common->macaddr);
	high_id = get_unaligned_le16(common->macaddr + 4);
	ath5k_hw_reg_write(ah, low_id, AR5K_STA_ID0);
	ath5k_hw_reg_write(ah, pcu_reg | high_id, AR5K_STA_ID1);


	if (ah->ah_version == AR5K_AR5210)
		ath5k_hw_reg_write(ah, beacon_reg, AR5K_BCR);

	return 0;
}
