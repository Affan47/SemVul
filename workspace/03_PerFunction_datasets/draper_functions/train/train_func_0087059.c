__ath9k_hw_init(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int r = 0;

	ath9k_hw_read_revisions(ah);

	switch (ah->hw_version.macVersion) {
	case AR_SREV_VERSION_5416_PCI:
	case AR_SREV_VERSION_5416_PCIE:
	case AR_SREV_VERSION_9160:
	case AR_SREV_VERSION_9100:
	case AR_SREV_VERSION_9280:
	case AR_SREV_VERSION_9285:
	case AR_SREV_VERSION_9287:
	case AR_SREV_VERSION_9271:
	case AR_SREV_VERSION_9300:
	case AR_SREV_VERSION_9330:
	case AR_SREV_VERSION_9485:
	case AR_SREV_VERSION_9340:
	case AR_SREV_VERSION_9462:
	case AR_SREV_VERSION_9550:
	case AR_SREV_VERSION_9565:
	case AR_SREV_VERSION_9531:
	case AR_SREV_VERSION_9561:
		break;
	default:
		ath_err(common,
			"Mac Chip Rev 0x%02x.%x is not supported by this driver\n",
			ah->hw_version.macVersion, ah->hw_version.macRev);
		return -EOPNOTSUPP;
	}


	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->WARegVal = REG_READ(ah, AR_WA);
		ah->WARegVal |= (AR_WA_D3_L1_DISABLE |
				 AR_WA_ASPM_TIMER_BASED_DISABLE);
	}

	if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_POWER_ON)) {
		ath_err(common, "Couldn't reset chip\n");
		return -EIO;
	}

	if (AR_SREV_9565(ah)) {
		ah->WARegVal |= AR_WA_BIT22;
		REG_WRITE(ah, AR_WA, ah->WARegVal);
	}

	ath9k_hw_init_defaults(ah);
	ath9k_hw_init_config(ah);

	r = ath9k_hw_attach_ops(ah);
	if (r)
		return r;

	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE)) {
		ath_err(common, "Couldn't wakeup chip\n");
		return -EIO;
	}

	if (AR_SREV_9271(ah) || AR_SREV_9100(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9330(ah) || AR_SREV_9550(ah))
		ah->is_pciexpress = false;

	ah->hw_version.phyRev = REG_READ(ah, AR_PHY_CHIP_ID);
	ath9k_hw_init_cal_settings(ah);

	if (!ah->is_pciexpress)
		ath9k_hw_disablepcie(ah);

	r = ath9k_hw_post_init(ah);
	if (r)
		return r;

	ath9k_hw_init_mode_gain_regs(ah);
	r = ath9k_hw_fill_cap_info(ah);
	if (r)
		return r;

	r = ath9k_hw_init_macaddr(ah);
	if (r) {
		ath_err(common, "Failed to initialize MAC address\n");
		return r;
	}

	ath9k_hw_init_hang_checks(ah);

	common->state = ATH_HW_INITIALIZED;

	return 0;
}
