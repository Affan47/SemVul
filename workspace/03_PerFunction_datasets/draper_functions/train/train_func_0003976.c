ath9k_hw_read_revisions(struct ath_hw *ah)
{
	u32 val;

	if (ah->get_mac_revision)
		ah->hw_version.macRev = ah->get_mac_revision();

	switch (ah->hw_version.devid) {
	case AR5416_AR9100_DEVID:
		ah->hw_version.macVersion = AR_SREV_VERSION_9100;
		break;
	case AR9300_DEVID_AR9330:
		ah->hw_version.macVersion = AR_SREV_VERSION_9330;
		if (!ah->get_mac_revision) {
			val = REG_READ(ah, AR_SREV);
			ah->hw_version.macRev = MS(val, AR_SREV_REVISION2);
		}
		return;
	case AR9300_DEVID_AR9340:
		ah->hw_version.macVersion = AR_SREV_VERSION_9340;
		return;
	case AR9300_DEVID_QCA955X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9550;
		return;
	case AR9300_DEVID_AR953X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9531;
		return;
	case AR9300_DEVID_QCA956X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9561;
		return;
	}

	val = REG_READ(ah, AR_SREV) & AR_SREV_ID;

	if (val == 0xFF) {
		val = REG_READ(ah, AR_SREV);
		ah->hw_version.macVersion =
			(val & AR_SREV_VERSION2) >> AR_SREV_TYPE2_S;
		ah->hw_version.macRev = MS(val, AR_SREV_REVISION2);

		if (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			ah->is_pciexpress = true;
		else
			ah->is_pciexpress = (val &
					     AR_SREV_TYPE2_HOST_MODE) ? 0 : 1;
	} else {
		if (!AR_SREV_9100(ah))
			ah->hw_version.macVersion = MS(val, AR_SREV_VERSION);

		ah->hw_version.macRev = val & AR_SREV_REVISION;

		if (ah->hw_version.macVersion == AR_SREV_VERSION_5416_PCIE)
			ah->is_pciexpress = true;
	}
}
