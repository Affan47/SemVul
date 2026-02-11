ar5416NumTxPending(struct ath_hal *ah, a_uint32_t q)
{
        a_uint32_t npend;

        HALASSERT(q < AH_PRIVATE(ah)->ah_caps.halTotalQueues);
        HALASSERT(AH5416(ah)->ah_txq[q].tqi_type != HAL_TX_QUEUE_INACTIVE);

	npend = ioread32_mac(AR_QSTS(q))
		& AR_Q_STS_PEND_FR_CNT;
        if (npend == 0) {


		if (ioread32_mac(AR_Q_TXE) & (1 << q))
                        npend = 1;
        }
#ifdef DEBUG
        if (npend && (AH5416(ah)->ah_txq[q].tqi_type == HAL_TX_QUEUE_CAB)) {
		if (ioread32_mac(AR_Q_RDYTIMESHDN)
				& (1 << q)) {
                        isrPrintf("RTSD on CAB queue\n");

			iowrite32_mac(AR_Q_RDYTIMESHDN, 1 << q);
                }
        }
#endif
        return npend;
}
