HandleStdEndPointReq(TSetupPacket	*pSetup, int *piLen, U8 **ppbData)
{
	U8	*pbData = *ppbData;

	switch (pSetup->bRequest) {
	case REQ_GET_STATUS:

		pbData[0] = (USBHwEPGetStatus(pSetup->wIndex) & EP_STATUS_STALLED) ? 1 : 0;
		pbData[1] = 0;
		*piLen = 2;
		break;

	case REQ_CLEAR_FEATURE:
		if (pSetup->wValue == FEA_ENDPOINT_HALT) {

			USBHwEPStall(pSetup->wIndex, FALSE);
			break;
		}

		return FALSE;

	case REQ_SET_FEATURE:
		if (pSetup->wValue == FEA_ENDPOINT_HALT) {

			USBHwEPStall(pSetup->wIndex, TRUE);
			break;
		}

		return FALSE;

	case REQ_SYNCH_FRAME:
		DBG("EP req %d not implemented\n", pSetup->bRequest);
		return FALSE;

	default:
		DBG("Illegal EP req %d\n", pSetup->bRequest);
		return FALSE;
	}

	return TRUE;
}
