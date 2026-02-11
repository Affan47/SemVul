xgs_do_dma(bkn_switch_info_t *sinfo, int budget)
{
    int rx_dcbs_done = 0, tx_dcbs_done = 0;
    uint32_t dma_stat;
    int chan;

    DEV_READ32(sinfo, CMIC_DMA_STATr, &dma_stat);

    for (chan = 0; chan < NUM_RX_CHAN; chan++) {
        if (dma_stat & DS_DESC_DONE_TST(XGS_DMA_RX_CHAN + chan)) {
            xgs_dma_desc_clear(sinfo, XGS_DMA_RX_CHAN + chan);
            rx_dcbs_done += bkn_do_rx(sinfo, chan, budget - rx_dcbs_done);
            bkn_rx_desc_done(sinfo, chan);
        }

        if (dma_stat & DS_CHAIN_DONE_TST(XGS_DMA_RX_CHAN + chan)) {
            xgs_dma_chain_clear(sinfo, XGS_DMA_RX_CHAN + chan);
            bkn_rx_chain_done(sinfo, chan);
        }
    }

    if (dma_stat & DS_CHAIN_DONE_TST(XGS_DMA_TX_CHAN)) {
        xgs_dma_chain_clear(sinfo, XGS_DMA_TX_CHAN);
        tx_dcbs_done = bkn_do_tx(sinfo);
        bkn_tx_chain_done(sinfo, tx_dcbs_done);
    }

    return rx_dcbs_done;
}
