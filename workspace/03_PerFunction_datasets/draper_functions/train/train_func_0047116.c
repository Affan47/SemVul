rcGetNextLowerValidTxRate(const RATE_TABLE_11N *pRateTable, TX_RATE_CTRL *pRc,
                          A_UINT8 curValidTxRate, A_UINT8 *pNextIndex)
{
	A_INT8 i;

	for (i = 1; i < pRc->maxValidRate ; i++) {
		if (pRc->validRateIndex[i] == curValidTxRate) {
			*pNextIndex = pRc->validRateIndex[i-1];
			return TRUE;
		}
	}

	return FALSE;
}
