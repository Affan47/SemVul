SetCCKContinuousTx(struct _adapter *pAdapter, u8 bStart)
{
	u32 cckrate;

	if (bStart) {

		if (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn)) {

			set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bEnable);
		}

		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);

		cckrate  = pAdapter->mppriv.curr_rateidx;
		set_bb_reg(pAdapter, rCCK0_System, bCCKTxRate, cckrate);

		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x2);

		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
	} else {

		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x0);

		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);

		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	}
}
