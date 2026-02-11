realtek_open ( struct net_device *netdev ) {
	struct realtek_nic *rtl = netdev->priv;
	uint32_t tcr;
	uint32_t rcr;
	int rc;


	if ( ( rc = realtek_create_ring ( rtl, &rtl->tx ) ) != 0 )
		goto err_create_tx;


	if ( ( rc = realtek_create_ring ( rtl, &rtl->rx ) ) != 0 )
		goto err_create_rx;


	if ( ( rc = realtek_create_buffer ( rtl ) ) != 0 )
		goto err_create_buffer;


	writel ( 0xffffffffUL, rtl->regs + RTL_MAR0 );
	writel ( 0xffffffffUL, rtl->regs + RTL_MAR4 );


	writeb ( ( RTL_CR_TE | RTL_CR_RE ), rtl->regs + RTL_CR );


	tcr = readl ( rtl->regs + RTL_TCR );
	tcr &= ~RTL_TCR_MXDMA_MASK;
	tcr |= RTL_TCR_MXDMA_DEFAULT;
	writel ( tcr, rtl->regs + RTL_TCR );


	rcr = readl ( rtl->regs + RTL_RCR );
	rcr &= ~( RTL_RCR_RXFTH_MASK | RTL_RCR_RBLEN_MASK |
		  RTL_RCR_MXDMA_MASK );
	rcr |= ( RTL_RCR_RXFTH_DEFAULT | RTL_RCR_RBLEN_DEFAULT |
		 RTL_RCR_MXDMA_DEFAULT | RTL_RCR_WRAP | RTL_RCR_AB |
		 RTL_RCR_AM | RTL_RCR_APM | RTL_RCR_AAP );
	writel ( rcr, rtl->regs + RTL_RCR );


	realtek_refill_rx ( rtl );


	realtek_check_link ( netdev );

	return 0;

	realtek_destroy_buffer ( rtl );
 err_create_buffer:
	realtek_destroy_ring ( rtl, &rtl->rx );
 err_create_rx:
	realtek_destroy_ring ( rtl, &rtl->tx );
 err_create_tx:
	return rc;
}
