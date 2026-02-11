de4x5_sw_reset(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int i, j, status = 0;
    s32 bmr, omr;


    if (!lp->useSROM) {
	if (lp->phy[lp->active].id != 0) {
	    lp->infoblock_csr6 = OMR_SDP | OMR_PS | OMR_HBD;
	} else {
	    lp->infoblock_csr6 = OMR_SDP | OMR_TTM;
	}
	de4x5_switch_mac_port(dev);
    }


    bmr = (lp->chipset==DC21140 ? PBL_8 : PBL_4) | DESC_SKIP_LEN | DE4X5_CACHE_ALIGN;
    bmr |= ((lp->chipset & ~0x00ff)==DC2114x ? BMR_RML : 0);
    outl(bmr, DE4X5_BMR);

    omr = inl(DE4X5_OMR) & ~OMR_PR;
    if (lp->chipset == DC21140) {
	omr |= (OMR_SDP | OMR_SB);
    }
    lp->setup_f = PERFECT;
    outl(lp->dma_rings, DE4X5_RRBA);
    outl(lp->dma_rings + NUM_RX_DESC * sizeof(struct de4x5_desc),
	 DE4X5_TRBA);

    lp->rx_new = lp->rx_old = 0;
    lp->tx_new = lp->tx_old = 0;

    for (i = 0; i < lp->rxRingSize; i++) {
	lp->rx_ring[i].status = cpu_to_le32(R_OWN);
    }

    for (i = 0; i < lp->txRingSize; i++) {
	lp->tx_ring[i].status = cpu_to_le32(0);
    }

    barrier();


    SetMulticastFilter(dev);

    load_packet(dev, lp->setup_frame, PERFECT_F|TD_SET|SETUP_FRAME_LEN, (struct sk_buff *)1);
    outl(omr|OMR_ST, DE4X5_OMR);


    for (j=0, i=0;(i<500) && (j==0);i++) {
	mdelay(1);
	if ((s32)le32_to_cpu(lp->tx_ring[lp->tx_new].status) >= 0) j=1;
    }
    outl(omr, DE4X5_OMR);

    if (j == 0) {
	printk("%s: Setup frame timed out, status %08x\n", dev->name,
	       inl(DE4X5_STS));
	status = -EIO;
    }

    lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;
    lp->tx_old = lp->tx_new;

    return status;
}
