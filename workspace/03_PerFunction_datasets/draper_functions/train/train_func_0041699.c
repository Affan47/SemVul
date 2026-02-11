bkn_create_sinfo(int dev_no)
{
    bkn_switch_info_t *sinfo;
    uint32_t val;
    int chan;

    if ((sinfo = kmalloc(sizeof(*sinfo), GFP_KERNEL)) == NULL) {
        return NULL;
    }
    memset(sinfo, 0, sizeof(*sinfo));
    INIT_LIST_HEAD(&sinfo->ndev_list);
    INIT_LIST_HEAD(&sinfo->rxpf_list);
    sinfo->base_addr = lkbde_get_dev_virt(dev_no);
    sinfo->dma_dev = lkbde_get_dma_dev(dev_no);
    sinfo->pdev = lkbde_get_hw_dev(dev_no);
    sinfo->dev_no = dev_no;
    sinfo->evt_idx = -1;

    spin_lock_init(&sinfo->lock);

    init_timer(&sinfo->timer);
    sinfo->timer.expires = jiffies + 1;
    sinfo->timer.data = (unsigned long)sinfo;
    sinfo->timer.function = bkn_timer;

    INIT_LIST_HEAD(&sinfo->tx.api_dcb_list);

    for (chan = 0; chan < NUM_RX_CHAN; chan++) {
        INIT_LIST_HEAD(&sinfo->rx[chan].api_dcb_list);
        sinfo->rx[chan].use_rx_skb = use_rx_skb;
    }


    if (use_rx_skb == 2) {
        sinfo->rx[0].use_rx_skb = 0;
    }

    init_timer(&sinfo->rxtick);
    sinfo->rxtick.expires = jiffies + 1;
    sinfo->rxtick.data = (unsigned long)sinfo;
    sinfo->rxtick.function = bkn_rxtick;

    for (chan = 0; chan < NUM_RX_CHAN; chan++) {
        sinfo->rx[chan].rate_max = rx_rate[chan];
        sinfo->rx[chan].burst_max = rx_burst[chan];
    }
    bkn_rx_rate_config(sinfo);

    add_timer(&sinfo->rxtick);

    list_add_tail(&sinfo->list, &_sinfo_list);

    sinfo->cmic_type = 'e';
    DEV_READ32(sinfo, CMIC_DEV_REV_IDr, &val);
    if (val == 0) {
        sinfo->cmic_type = 'm';
        DEV_READ32(sinfo, CMICM_DEV_REV_IDr, &val);
    }

    DBG_VERB(("Check dev/rev: 0x%08x\n", val));

    return sinfo;
}
