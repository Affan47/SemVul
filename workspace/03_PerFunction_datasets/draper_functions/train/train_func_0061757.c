xgbe_serdes_complete_ratechange(struct xgbe_prv_data *pdata)
{
	unsigned int wait;
	u16 status;


	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, RATECHANGE, 0);


	wait = XGBE_RATECHANGE_COUNT;
	while (wait--) {
		usleep_range(50, 75);

		status = XSIR0_IOREAD(pdata, SIR0_STATUS);
		if (XSIR_GET_BITS(status, SIR0_STATUS, RX_READY) &&
		    XSIR_GET_BITS(status, SIR0_STATUS, TX_READY))
			goto rx_reset;
	}

	netif_dbg(pdata, link, pdata->netdev, "SerDes rx/tx not ready (%#hx)\n",
		  status);

rx_reset:

	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 0);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 1);
}
