dwc2_xfercomp_isoc_split_in(struct dwc2_hsotg *hsotg,
				       struct dwc2_host_chan *chan, int chnum,
				       struct dwc2_qtd *qtd)
{
	struct dwc2_hcd_iso_packet_desc *frame_desc;
	u32 len;

	if (!qtd->urb)
		return 0;

	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index];
	len = dwc2_get_actual_xfer_length(hsotg, chan, chnum, qtd,
					  DWC2_HC_XFER_COMPLETE, NULL);
	if (!len) {
		qtd->complete_split = 0;
		qtd->isoc_split_offset = 0;
		return 0;
	}

	frame_desc->actual_length += len;

	if (chan->align_buf) {
		dev_vdbg(hsotg->dev, "%s(): non-aligned buffer\n", __func__);
		dma_unmap_single(hsotg->dev, chan->qh->dw_align_buf_dma,
				chan->qh->dw_align_buf_size, DMA_FROM_DEVICE);
		memcpy(qtd->urb->buf + frame_desc->offset +
		       qtd->isoc_split_offset, chan->qh->dw_align_buf, len);
	}

	qtd->isoc_split_offset += len;

	if (frame_desc->actual_length >= frame_desc->length) {
		frame_desc->status = 0;
		qtd->isoc_frame_index++;
		qtd->complete_split = 0;
		qtd->isoc_split_offset = 0;
	}

	if (qtd->isoc_frame_index == qtd->urb->packet_count) {
		dwc2_host_complete(hsotg, qtd, 0);
		dwc2_release_channel(hsotg, chan, qtd,
				     DWC2_HC_XFER_URB_COMPLETE);
	} else {
		dwc2_release_channel(hsotg, chan, qtd,
				     DWC2_HC_XFER_NO_HALT_STATUS);
	}

	return 1;
}
