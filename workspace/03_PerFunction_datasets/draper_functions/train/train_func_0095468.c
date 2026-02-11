ar9287_dump_modal_eeprom(char *buf, u32 len, u32 size,
				    struct modal_eep_ar9287_header *modal_hdr)
{
	PR_EEP("Chain0 Ant. Control", modal_hdr->antCtrlChain[0]);
	PR_EEP("Chain1 Ant. Control", modal_hdr->antCtrlChain[1]);
	PR_EEP("Ant. Common Control", modal_hdr->antCtrlCommon);
	PR_EEP("Chain0 Ant. Gain", modal_hdr->antennaGainCh[0]);
	PR_EEP("Chain1 Ant. Gain", modal_hdr->antennaGainCh[1]);
	PR_EEP("Switch Settle", modal_hdr->switchSettling);
	PR_EEP("Chain0 TxRxAtten", modal_hdr->txRxAttenCh[0]);
	PR_EEP("Chain1 TxRxAtten", modal_hdr->txRxAttenCh[1]);
	PR_EEP("Chain0 RxTxMargin", modal_hdr->rxTxMarginCh[0]);
	PR_EEP("Chain1 RxTxMargin", modal_hdr->rxTxMarginCh[1]);
	PR_EEP("ADC Desired size", modal_hdr->adcDesiredSize);
	PR_EEP("txEndToXpaOff", modal_hdr->txEndToXpaOff);
	PR_EEP("txEndToRxOn", modal_hdr->txEndToRxOn);
	PR_EEP("txFrameToXpaOn", modal_hdr->txFrameToXpaOn);
	PR_EEP("CCA Threshold)", modal_hdr->thresh62);
	PR_EEP("Chain0 NF Threshold", modal_hdr->noiseFloorThreshCh[0]);
	PR_EEP("Chain1 NF Threshold", modal_hdr->noiseFloorThreshCh[1]);
	PR_EEP("xpdGain", modal_hdr->xpdGain);
	PR_EEP("External PD", modal_hdr->xpd);
	PR_EEP("Chain0 I Coefficient", modal_hdr->iqCalICh[0]);
	PR_EEP("Chain1 I Coefficient", modal_hdr->iqCalICh[1]);
	PR_EEP("Chain0 Q Coefficient", modal_hdr->iqCalQCh[0]);
	PR_EEP("Chain1 Q Coefficient", modal_hdr->iqCalQCh[1]);
	PR_EEP("pdGainOverlap", modal_hdr->pdGainOverlap);
	PR_EEP("xPA Bias Level", modal_hdr->xpaBiasLvl);
	PR_EEP("txFrameToDataStart", modal_hdr->txFrameToDataStart);
	PR_EEP("txFrameToPaOn", modal_hdr->txFrameToPaOn);
	PR_EEP("HT40 Power Inc.", modal_hdr->ht40PowerIncForPdadc);
	PR_EEP("Chain0 bswAtten", modal_hdr->bswAtten[0]);
	PR_EEP("Chain1 bswAtten", modal_hdr->bswAtten[1]);
	PR_EEP("Chain0 bswMargin", modal_hdr->bswMargin[0]);
	PR_EEP("Chain1 bswMargin", modal_hdr->bswMargin[1]);
	PR_EEP("HT40 Switch Settle", modal_hdr->swSettleHt40);
	PR_EEP("AR92x7 Version", modal_hdr->version);
	PR_EEP("DriverBias1", modal_hdr->db1);
	PR_EEP("DriverBias2", modal_hdr->db1);
	PR_EEP("CCK OutputBias", modal_hdr->ob_cck);
	PR_EEP("PSK OutputBias", modal_hdr->ob_psk);
	PR_EEP("QAM OutputBias", modal_hdr->ob_qam);
	PR_EEP("PAL_OFF OutputBias", modal_hdr->ob_pal_off);

	return len;
}
