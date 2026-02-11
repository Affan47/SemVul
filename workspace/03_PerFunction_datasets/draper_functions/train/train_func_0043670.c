ar5008_hw_set_rf_regs(struct ath_hw *ah,
				  struct ath9k_channel *chan,
				  u16 modesIndex)
{
	u32 eepMinorRev;
	u32 ob5GHz = 0, db5GHz = 0;
	u32 ob2GHz = 0, db2GHz = 0;
	unsigned int regWrites = 0;


	if (AR_SREV_9280_20_OR_LATER(ah))
		return 1;


	eepMinorRev = ah->eep_ops->get_eeprom(ah, EEP_MINOR_REV);


	ar5008_rf_bank_setup(ah->analogBank0Data, &ah->iniBank0, 1);


	ar5008_rf_bank_setup(ah->analogBank1Data, &ah->iniBank1, 1);


	ar5008_rf_bank_setup(ah->analogBank2Data, &ah->iniBank2, 1);


	ar5008_rf_bank_setup(ah->analogBank3Data, &ah->iniBank3,
		      modesIndex);
	{
		unsigned int i;
		for (i = 0; i < ah->iniBank6TPC.ia_rows; i++) {
			ah->analogBank6Data[i] =
			    INI_RA(&ah->iniBank6TPC, i, modesIndex);
		}
	}


	if (eepMinorRev >= 2) {
		if (IS_CHAN_2GHZ(chan)) {
			ob2GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_2);
			db2GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_2);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       ob2GHz, 3, 197, 0);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       db2GHz, 3, 194, 0);
		} else {
			ob5GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_5);
			db5GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_5);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       ob5GHz, 3, 203, 0);
			ar5008_hw_phy_modify_rx_buffer(ah->analogBank6Data,
						       db5GHz, 3, 200, 0);
		}
	}


	ar5008_rf_bank_setup(ah->analogBank7Data, &ah->iniBank7, 1);


	REG_WRITE_RF_ARRAY(&ah->iniBank0, ah->analogBank0Data,
			   regWrites);
	REG_WRITE_RF_ARRAY(&ah->iniBank1, ah->analogBank1Data,
			   regWrites);
	REG_WRITE_RF_ARRAY(&ah->iniBank2, ah->analogBank2Data,
			   regWrites);
	REG_WRITE_RF_ARRAY(&ah->iniBank3, ah->analogBank3Data,
			   regWrites);
	REG_WRITE_RF_ARRAY(&ah->iniBank6TPC, ah->analogBank6Data,
			   regWrites);
	REG_WRITE_RF_ARRAY(&ah->iniBank7, ah->analogBank7Data,
			   regWrites);

	return 1;
}
