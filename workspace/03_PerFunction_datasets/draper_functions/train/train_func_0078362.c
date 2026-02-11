USBHwEPWrite(U8 bEP, U8 *pbBuf, int iLen)
{
	int idx;

	idx = EP2IDX(bEP);


	USBCtrl = WR_EN | ((bEP & 0xF) << 2);


	USBTxPLen = iLen;


	while (USBCtrl & WR_EN) {
		USBTxData = (pbBuf[3] << 24) | (pbBuf[2] << 16) | (pbBuf[1] << 8) | pbBuf[0];
		pbBuf += 4;
	}


	USBHwCmd(CMD_EP_SELECT | idx);
	USBHwCmd(CMD_EP_VALIDATE_BUFFER);

	return iLen;
}
