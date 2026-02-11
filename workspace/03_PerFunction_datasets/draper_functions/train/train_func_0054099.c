rcRateGetIndex(struct ath_softc_tgt *sc, struct ath_node_target *an,
               const RATE_TABLE_11N *pRateTable ,
               A_UINT8 rix, A_UINT16 stepDown, A_UINT16 minRate)
{
	A_UINT32                j;
	A_UINT8                 nextIndex;
	struct atheros_node     *pSib = ATH_NODE_ATHEROS(an);
	TX_RATE_CTRL            *pRc = (TX_RATE_CTRL *)(pSib);

	if (minRate) {
		for (j = RATE_TABLE_11N_SIZE; j > 0; j-- ) {
			if (rcGetNextLowerValidTxRate(pRateTable, pRc, rix, &nextIndex)) {
				rix = nextIndex;
			} else {
				break;
			}
		}
	} else {
		for (j = stepDown; j > 0; j-- ) {
			if (rcGetNextLowerValidTxRate(pRateTable, pRc, rix, &nextIndex)) {
				rix = nextIndex;
			} else {
				break;
			}
		}
	}

	return rix;
}
