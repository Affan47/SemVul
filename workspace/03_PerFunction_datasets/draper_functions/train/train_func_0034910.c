bkn_match_rx_pkt(bkn_switch_info_t *sinfo, uint32_t *desc,
                 uint8_t *pkt, int chan, bkn_filter_t *cbf)
{
    struct list_head *list;
    bkn_filter_t *filter;
    kcom_filter_t scratch, *kf;
    uint8_t *oob = (uint8_t *)desc;
    int size, wsize;
    int idx, match;

    list_for_each(list, &sinfo->rxpf_list) {
        filter = (bkn_filter_t *)list;
        kf = &filter->kf;
        memcpy(&scratch.data.b[0],
               &oob[kf->oob_data_offset], kf->oob_data_size);
        memcpy(&scratch.data.b[kf->oob_data_size],
               &pkt[kf->pkt_data_offset], kf->pkt_data_size);
        size = kf->oob_data_size + kf->pkt_data_size;
        wsize = BYTES2WORDS(size);
        DBG_VERB(("Filter: size = %d (%d), data = 0x%08x, mask = 0x%08x\n",
                  size, wsize, kf->data.w[0], kf->mask.w[0]));
        match = 1;
        if (match) {
            if (kf->priority < (num_rx_prio * NUM_RX_CHAN)) {
                if (kf->priority < (num_rx_prio * chan) ||
                    kf->priority >= (num_rx_prio * (chan + 1))) {
                    match = 0;
                }
            }
        }
        if (match) {
            for (idx = 0; idx < wsize; idx++) {
                scratch.data.w[idx] &= kf->mask.w[idx];
                if (scratch.data.w[idx] != kf->data.w[idx]) {
                    match = 0;
                    break;
                }
            }
        }
        if (match) {
            if (kf->dest_type == KCOM_DEST_T_CB) {

                if (knet_filter_cb != NULL && cbf != NULL) {
                    size = desc[sinfo->dcb_wsize-1] & SOC_DCB_KNET_COUNT_MASK;
                    memset(cbf, 0, sizeof(*cbf));
                    memcpy(&cbf->kf, kf, sizeof(cbf->kf));
                    if (knet_filter_cb(pkt, size, sinfo->dev_no,
                                       desc, chan, &cbf->kf)) {
                        filter->hits++;
                        return cbf;
                    }
                } else {
                    DBG_FLTR(("Match, but not filter callback\n"));
                }
            } else {
                filter->hits++;
                return filter;
            }
        }
    }

    return NULL;
}
