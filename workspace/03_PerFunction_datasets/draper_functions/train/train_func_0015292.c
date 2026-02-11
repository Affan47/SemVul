SetOFDMContinuousTx(struct _adapter *pAdapter, u8 bStart)
{
	if (bStart) {

		if (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn)) {

			set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		}

		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, bDisable);

		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);

		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bEnable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
	} else {
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier,
			   bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
		msleep(20);

		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	}
}
