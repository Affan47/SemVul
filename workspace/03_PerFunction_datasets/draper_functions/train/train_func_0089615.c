lmc_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 flag;
    int entry;
    unsigned long flags;

    lmc_trace(dev, "lmc_start_xmit in");

    spin_lock_irqsave(&sc->lmc_lock, flags);


    entry = sc->lmc_next_tx % LMC_TXDESCS;

    sc->lmc_txq[entry] = skb;
    sc->lmc_txring[entry].buffer1 = virt_to_bus (skb->data);

    LMC_CONSOLE_LOG("xmit", skb->data, skb->len);

#ifndef GCOM

    if (sc->lmc_next_tx - sc->lmc_taint_tx < LMC_TXDESCS / 2)
    {

        flag = 0x60000000;
        netif_wake_queue(dev);
    }
    else if (sc->lmc_next_tx - sc->lmc_taint_tx == LMC_TXDESCS / 2)
    {

        flag = 0xe0000000;
        netif_wake_queue(dev);
    }
    else if (sc->lmc_next_tx - sc->lmc_taint_tx < LMC_TXDESCS - 1)
    {

        flag = 0x60000000;
        netif_wake_queue(dev);
    }
    else
    {

        flag = 0xe0000000;
        sc->lmc_txfull = 1;
        netif_stop_queue(dev);
    }
#else
    flag = LMC_TDES_INTERRUPT_ON_COMPLETION;

    if (sc->lmc_next_tx - sc->lmc_taint_tx >= LMC_TXDESCS - 1)
    {
        sc->lmc_txfull = 1;
	netif_stop_queue(dev);
	sc->extra_stats.tx_tbusy1++;
        LMC_EVENT_LOG(LMC_EVENT_TBUSY1, entry, 0);
    }
#endif


    if (entry == LMC_TXDESCS - 1)
	flag |= LMC_TDES_END_OF_RING;


    flag = sc->lmc_txring[entry].length = (skb->len) | flag |
						sc->TxDescriptControlInit;


    sc->extra_stats.tx_NoCompleteCnt++;
    sc->lmc_next_tx++;


    LMC_EVENT_LOG(LMC_EVENT_XMT, flag, entry);
    sc->lmc_txring[entry].status = 0x80000000;


    LMC_CSR_WRITE (sc, csr_txpoll, 0);

    spin_unlock_irqrestore(&sc->lmc_lock, flags);

    lmc_trace(dev, "lmc_start_xmit_out");
    return NETDEV_TX_OK;
}
