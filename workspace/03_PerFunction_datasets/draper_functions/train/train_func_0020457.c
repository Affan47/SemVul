ath9k_hw_4k_get_eeprom(struct ath_hw *ah,
				  enum eeprom_param param)
{
	struct ar5416_eeprom_4k *eep = &ah->eeprom.map4k;
	struct modal_eep_4k_header *pModal = &eep->modalHeader;
	struct base_eep_header_4k *pBase = &eep->baseEepHeader;
	u16 ver_minor;

	ver_minor = pBase->version & AR5416_EEP_VER_MINOR_MASK;

	switch (param) {
	case EEP_NFTHRESH_2:
		return pModal->noiseFloorThreshCh[0];
	case EEP_MAC_LSW:
		return pBase->macAddr[0] << 8 | pBase->macAddr[1];
	case EEP_MAC_MID:
		return pBase->macAddr[2] << 8 | pBase->macAddr[3];
	case EEP_MAC_MSW:
		return pBase->macAddr[4] << 8 | pBase->macAddr[5];
	case EEP_REG_0:
		return pBase->regDmn[0];
	case EEP_REG_1:
		return pBase->regDmn[1];
	case EEP_OP_CAP:
		return pBase->deviceCap;
	case EEP_OP_MODE:
		return pBase->opCapFlags;
	case EEP_RF_SILENT:
		return pBase->rfSilent;
	case EEP_OB_2:
		return pModal->ob_0;
	case EEP_DB_2:
		return pModal->db1_1;
	case EEP_MINOR_REV:
		return ver_minor;
	case EEP_TX_MASK:
		return pBase->txMask;
	case EEP_RX_MASK:
		return pBase->rxMask;
	case EEP_FRAC_N_5G:
		return 0;
	case EEP_PWR_TABLE_OFFSET:
		return AR5416_PWR_TABLE_OFFSET_DB;
	case EEP_MODAL_VER:
		return pModal->version;
	case EEP_ANT_DIV_CTL1:
		return pModal->antdiv_ctl1;
	case EEP_TXGAIN_TYPE:
		if (ver_minor >= AR5416_EEP_MINOR_VER_19)
			return pBase->txGainType;
		else
			return AR5416_EEP_TXGAIN_ORIGINAL;
	default:
		return 0;
	}
}
