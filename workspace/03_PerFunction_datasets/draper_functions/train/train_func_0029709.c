ia_update_stats(IADEV *iadev) {
    if (!iadev->carrier_detect)
        return;
    iadev->rx_cell_cnt += readw(iadev->reass_reg+CELL_CTR0)&0xffff;
    iadev->rx_cell_cnt += (readw(iadev->reass_reg+CELL_CTR1) & 0xffff) << 16;
    iadev->drop_rxpkt +=  readw(iadev->reass_reg + DRP_PKT_CNTR ) & 0xffff;
    iadev->drop_rxcell += readw(iadev->reass_reg + ERR_CNTR) & 0xffff;
    iadev->tx_cell_cnt += readw(iadev->seg_reg + CELL_CTR_LO_AUTO)&0xffff;
    iadev->tx_cell_cnt += (readw(iadev->seg_reg+CELL_CTR_HIGH_AUTO)&0xffff)<<16;
    return;
}
