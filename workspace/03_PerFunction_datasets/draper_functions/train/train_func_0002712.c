bkn_clean_tx_dcbs(bkn_switch_info_t *sinfo)
{
    bkn_desc_info_t *desc;

    DBG_DCB_TX(("Cleaning Tx DCBs (%d %d).\n",
                sinfo->tx.cur, sinfo->tx.dirty));
    while (sinfo->tx.free < MAX_TX_DCBS) {
        desc = &sinfo->tx.desc[sinfo->tx.dirty];
        if (desc->skb != NULL) {
            DBG_SKB(("Cleaning Tx SKB from DCB %d.\n",
                     sinfo->tx.dirty));
            DMA_UNMAP_SINGLE(sinfo->dma_dev,
                             desc->skb_dma, desc->dma_size,
                             DMA_TODEV);
            desc->skb_dma = 0;
            dev_kfree_skb_any(desc->skb);
            desc->skb = NULL;
        }
        if (++sinfo->tx.dirty >= MAX_TX_DCBS) {
            sinfo->tx.dirty = 0;
        }
        sinfo->tx.free++;
    }
    sinfo->tx.api_active = 0;
    DBG_DCB_TX(("Cleaned Tx DCBs (%d %d).\n",
                sinfo->tx.cur, sinfo->tx.dirty));
}
