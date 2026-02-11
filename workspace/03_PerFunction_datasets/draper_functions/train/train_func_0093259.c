rhine_reset (struct nic *nic)
{
    struct rhine_private *tp = (struct rhine_private *) nic->priv_data;
    int ioaddr = tp->ioaddr;
    int i, j;
    int FDXFlag, CRbak;
    void *rx_ring_tmp;
    void *tx_ring_tmp;
    void *rx_bufs_tmp;
    void *tx_bufs_tmp;
    unsigned long rx_ring_tmp1;
    unsigned long tx_ring_tmp1;
    unsigned long rx_bufs_tmp1;
    unsigned long tx_bufs_tmp1;


    tx_bufs_tmp = rhine_buffers.txbuf;
    tx_ring_tmp = rhine_buffers.txdesc;
    rx_bufs_tmp = rhine_buffers.rxbuf;
    rx_ring_tmp = rhine_buffers.rxdesc;


    rx_ring_tmp1 = virt_to_bus ( rx_ring_tmp );
    j = (rx_ring_tmp1 + 32) & (~0x1f);

    tp->rx_ring = (struct rhine_rx_desc *) bus_to_virt (j);

    tx_ring_tmp1 = virt_to_bus ( tx_ring_tmp );
    j = (tx_ring_tmp1 + 32) & (~0x1f);
    tp->tx_ring = (struct rhine_tx_desc *) bus_to_virt (j);


    tx_bufs_tmp1 = virt_to_bus ( tx_bufs_tmp );
    j = (int) (tx_bufs_tmp1 + 32) & (~0x1f);
    tx_bufs_tmp = bus_to_virt (j);


    rx_bufs_tmp1 = virt_to_bus ( rx_bufs_tmp );
    j = (int) (rx_bufs_tmp1 + 32) & (~0x1f);
    rx_bufs_tmp = bus_to_virt (j);


    for (i = 0; i < RX_RING_SIZE; i++)
    {
	tp->rx_buffs[i] = (char *) rx_bufs_tmp;

	rx_bufs_tmp += 1536;
    }

    for (i = 0; i < TX_RING_SIZE; i++)
    {
	tp->tx_buffs[i] = (char *) tx_bufs_tmp;

	tx_bufs_tmp += 1536;
    }


    outb (CR1_SFRST, byCR1);
    MIIDelay ();


    rhine_init_ring (nic);

    outl (virt_to_bus (tp->rx_ring), dwCurrentRxDescAddr);
    outl (virt_to_bus (tp->tx_ring), dwCurrentTxDescAddr);


    set_rx_mode(nic);


    outb (0x3e, byBCR0);
    outb (0x38, byBCR1);
    outb (0x2c, byRCR);
    outb (0x60, byTCR);

    FDXFlag = QueryAuto (ioaddr);
    if (FDXFlag == 1)
    {
	outb (CFGD_CFDX, byCFGD);
	outw (CR_FDX, byCR0);
    }


    CRbak = inw (byCR0);
    CRbak = CRbak & 0xFFFB;
    outw ((CRbak | CR_STRT | CR_TXON | CR_RXON | CR_DPOLL), byCR0);


    outw (0, byIMR0);
}
