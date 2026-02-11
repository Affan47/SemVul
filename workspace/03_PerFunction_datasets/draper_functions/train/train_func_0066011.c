rcRateSetseries(const RATE_TABLE_11N *pRateTable ,
                struct ath_rc_series *series,
		A_UINT8 tries, A_UINT8 rix,
		A_BOOL rtsctsenable, A_UINT32 chainmask,int stbc)
{
	series->tries = tries;
	series->flags = (rtsctsenable? ATH_RC_RTSCTS_FLAG : 0) |
		(WLAN_RC_PHY_DS(pRateTable->info[rix].phy) ? ATH_RC_DS_FLAG : 0) |
		(WLAN_RC_PHY_40(pRateTable->info[rix].phy) ? ATH_RC_CW40_FLAG : 0) |
		(WLAN_RC_PHY_SGI(pRateTable->info[rix].phy) ? ATH_RC_HT40_SGI_FLAG : 0);
#ifdef MAGPIE_MERLIN
	if (stbc) {

		if (pRateTable->info[rix].rateCode >= 0x80 &&
		    pRateTable->info[rix].rateCode <= 0x87)
		{
			series->flags |= ATH_RC_TX_STBC_FLAG;
		}
	}
#endif
	series->rix = pRateTable->info[rix].baseIndex;
	series->max4msframelen = pRateTable->info[rix].max4msframelen;
	series->txrateKbps = pRateTable->info[rix].rateKbps;


#ifndef ATH_ENABLE_WLAN_FOR_K2
	if(chainmask == 7)
		series->tx_chainmask = pRateTable->info[rix].txChainMask_3ch;
	else if(chainmask == 1)
		series->tx_chainmask = 1;
	else
		series->tx_chainmask = pRateTable->info[rix].txChainMask_2ch;
#else
	series->tx_chainmask = 1;
#endif
}
