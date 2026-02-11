build_srb(struct scsi_cmnd *cmd, struct DeviceCtlBlk *dcb,
		struct ScsiReqBlk *srb)
{
	int nseg;
	enum dma_data_direction dir = cmd->sc_data_direction;
	dprintkdbg(DBG_0, "build_srb: (0x%p) <%02i-%i>\n",
		cmd, dcb->target_id, dcb->target_lun);

	srb->dcb = dcb;
	srb->cmd = cmd;
	srb->sg_count = 0;
	srb->total_xfer_length = 0;
	srb->sg_bus_addr = 0;
	srb->sg_index = 0;
	srb->adapter_status = 0;
	srb->target_status = 0;
	srb->msg_count = 0;
	srb->status = 0;
	srb->flag = 0;
	srb->state = 0;
	srb->retry_count = 0;
	srb->tag_number = TAG_NONE;
	srb->scsi_phase = PH_BUS_FREE;
	srb->end_message = 0;

	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);

	if (dir == PCI_DMA_NONE || !nseg) {
		dprintkdbg(DBG_0,
			"build_srb: [0] len=%d buf=%p use_sg=%d !MAP=%08x\n",
			   cmd->bufflen, scsi_sglist(cmd), scsi_sg_count(cmd),
			   srb->segment_x[0].address);
	} else {
		int i;
		u32 reqlen = scsi_bufflen(cmd);
		struct scatterlist *sg;
		struct SGentry *sgp = srb->segment_x;

		srb->sg_count = nseg;

		dprintkdbg(DBG_0,
			   "build_srb: [n] len=%d buf=%p use_sg=%d segs=%d\n",
			   reqlen, scsi_sglist(cmd), scsi_sg_count(cmd),
			   srb->sg_count);

		scsi_for_each_sg(cmd, sg, srb->sg_count, i) {
			u32 busaddr = (u32)sg_dma_address(sg);
			u32 seglen = (u32)sg->length;
			sgp[i].address = busaddr;
			sgp[i].length = seglen;
			srb->total_xfer_length += seglen;
		}
		sgp += srb->sg_count - 1;


		if (srb->total_xfer_length > reqlen) {
			sgp->length -= (srb->total_xfer_length - reqlen);
			srb->total_xfer_length = reqlen;
		}


		if (dcb->sync_period & WIDE_SYNC &&
		    srb->total_xfer_length % 2) {
			srb->total_xfer_length++;
			sgp->length++;
		}

		srb->sg_bus_addr = pci_map_single(dcb->acb->dev,
						srb->segment_x,
				            	SEGMENTX_LEN,
				            	PCI_DMA_TODEVICE);

		dprintkdbg(DBG_SG, "build_srb: [n] map sg %p->%08x(%05x)\n",
			srb->segment_x, srb->sg_bus_addr, SEGMENTX_LEN);
	}

	srb->request_length = srb->total_xfer_length;
}
