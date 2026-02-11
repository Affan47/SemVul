bkn_dma_abort_tx(bkn_switch_info_t *sinfo)
{
    bkn_dcb_chain_t *dcb_chain;

    DBG_VERB(("Aborting Tx DMA.\n"));

    dev_irq_mask_disable(sinfo, XGS_DMA_TX_CHAN, 1);

    dev_dma_chan_abort(sinfo, XGS_DMA_TX_CHAN, 10000);

    if (sinfo->tx.api_dcb_chain) {
        DBG_DCB_TX(("Freeing active Tx DCB chain.\n"));
        kfree(sinfo->tx.api_dcb_chain);
        sinfo->tx.api_dcb_chain = NULL;
    }
    while (!list_empty(&sinfo->tx.api_dcb_list)) {
        dcb_chain = list_entry(sinfo->tx.api_dcb_list.next,
                                   bkn_dcb_chain_t, list);
        list_del(&dcb_chain->list);
        DBG_DCB_TX(("Freeing Tx DCB chain.\n"));
        kfree(dcb_chain);
    }
    sinfo->tx.api_dcb_chain_end = NULL;

    return 0;
}
