dump_register_info(struct AdapterCtlBlk *acb,
		struct DeviceCtlBlk *dcb, struct ScsiReqBlk *srb)
{
	u16 pstat;
	struct pci_dev *dev = acb->dev;
	pci_read_config_word(dev, PCI_STATUS, &pstat);
	if (!dcb)
		dcb = acb->active_dcb;
	if (!srb && dcb)
		srb = dcb->active_srb;
	if (srb) {
		if (!srb->cmd)
			dprintkl(KERN_INFO, "dump: srb=%p cmd=%p OOOPS!\n",
				srb, srb->cmd);
		else
			dprintkl(KERN_INFO, "dump: srb=%p cmd=%p "
				 "cmnd=0x%02x <%02i-%i>\n",
				srb, srb->cmd,
				srb->cmd->cmnd[0], srb->cmd->device->id,
				(u8)srb->cmd->device->lun);
		printk("  sglist=%p cnt=%i idx=%i len=%zu\n",
		       srb->segment_x, srb->sg_count, srb->sg_index,
		       srb->total_xfer_length);
		printk("  state=0x%04x status=0x%02x phase=0x%02x (%sconn.)\n",
		       srb->state, srb->status, srb->scsi_phase,
		       (acb->active_dcb) ? "" : "not");
	}
	dprintkl(KERN_INFO, "dump: SCSI{status=0x%04x fifocnt=0x%02x "
		"signals=0x%02x irqstat=0x%02x sync=0x%02x target=0x%02x "
		"rselid=0x%02x ctr=0x%08x irqen=0x%02x config=0x%04x "
		"config2=0x%02x cmd=0x%02x selto=0x%02x}\n",
		DC395x_read16(acb, TRM_S1040_SCSI_STATUS),
		DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT),
		DC395x_read8(acb, TRM_S1040_SCSI_SIGNAL),
		DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS),
		DC395x_read8(acb, TRM_S1040_SCSI_SYNC),
		DC395x_read8(acb, TRM_S1040_SCSI_TARGETID),
		DC395x_read8(acb, TRM_S1040_SCSI_IDMSG),
		DC395x_read32(acb, TRM_S1040_SCSI_COUNTER),
		DC395x_read8(acb, TRM_S1040_SCSI_INTEN),
		DC395x_read16(acb, TRM_S1040_SCSI_CONFIG0),
		DC395x_read8(acb, TRM_S1040_SCSI_CONFIG2),
		DC395x_read8(acb, TRM_S1040_SCSI_COMMAND),
		DC395x_read8(acb, TRM_S1040_SCSI_TIMEOUT));
	dprintkl(KERN_INFO, "dump: DMA{cmd=0x%04x fifocnt=0x%02x fstat=0x%02x "
		"irqstat=0x%02x irqen=0x%02x cfg=0x%04x tctr=0x%08x "
		"ctctr=0x%08x addr=0x%08x:0x%08x}\n",
		DC395x_read16(acb, TRM_S1040_DMA_COMMAND),
		DC395x_read8(acb, TRM_S1040_DMA_FIFOCNT),
		DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT),
		DC395x_read8(acb, TRM_S1040_DMA_STATUS),
		DC395x_read8(acb, TRM_S1040_DMA_INTEN),
		DC395x_read16(acb, TRM_S1040_DMA_CONFIG),
		DC395x_read32(acb, TRM_S1040_DMA_XCNT),
		DC395x_read32(acb, TRM_S1040_DMA_CXCNT),
		DC395x_read32(acb, TRM_S1040_DMA_XHIGHADDR),
		DC395x_read32(acb, TRM_S1040_DMA_XLOWADDR));
	dprintkl(KERN_INFO, "dump: gen{gctrl=0x%02x gstat=0x%02x gtmr=0x%02x} "
		"pci{status=0x%04x}\n",
		DC395x_read8(acb, TRM_S1040_GEN_CONTROL),
		DC395x_read8(acb, TRM_S1040_GEN_STATUS),
		DC395x_read8(acb, TRM_S1040_GEN_TIMER),
		pstat);
}
