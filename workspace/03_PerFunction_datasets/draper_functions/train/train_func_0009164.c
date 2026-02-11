dwc2_init_isoc_dma_desc(struct dwc2_hsotg *hsotg,
				    struct dwc2_qh *qh, u16 skip_frames)
{
	struct dwc2_qtd *qtd;
	u32 max_xfer_size;
	u16 idx, inc, n_desc, ntd_max = 0;

	idx = qh->td_last;
	inc = qh->interval;
	n_desc = 0;

	if (qh->interval) {
		ntd_max = (dwc2_max_desc_num(qh) + qh->interval - 1) /
				qh->interval;
		if (skip_frames && !qh->channel)
			ntd_max -= skip_frames / qh->interval;
	}

	max_xfer_size = qh->dev_speed == USB_SPEED_HIGH ?
			MAX_ISOC_XFER_SIZE_HS : MAX_ISOC_XFER_SIZE_FS;

	list_for_each_entry(qtd, &qh->qtd_list, qtd_list_entry) {
		while (qh->ntd < ntd_max && qtd->isoc_frame_index_last <
						qtd->urb->packet_count) {
			if (n_desc > 1)
				qh->desc_list[n_desc - 1].status |= HOST_DMA_A;
			dwc2_fill_host_isoc_dma_desc(hsotg, qtd, qh,
						     max_xfer_size, idx);
			idx = dwc2_desclist_idx_inc(idx, inc, qh->dev_speed);
			n_desc++;
		}
		qtd->in_process = 1;
	}

	qh->td_last = idx;

#ifdef ISOC_URB_GIVEBACK_ASAP

	if (qh->ntd == ntd_max) {
		idx = dwc2_desclist_idx_dec(qh->td_last, inc, qh->dev_speed);
		qh->desc_list[idx].status |= HOST_DMA_IOC;
	}
#else


	if (n_desc > DESCNUM_THRESHOLD)


		idx = dwc2_desclist_idx_dec(idx, inc * ((qh->ntd + 1) / 2),
					    qh->dev_speed);
	else


		idx = dwc2_desclist_idx_dec(qh->td_last, inc, qh->dev_speed);

	qh->desc_list[idx].status |= HOST_DMA_IOC;
#endif

	if (n_desc) {
		qh->desc_list[n_desc - 1].status |= HOST_DMA_A;
		if (n_desc > 1)
			qh->desc_list[0].status |= HOST_DMA_A;
	}
}
