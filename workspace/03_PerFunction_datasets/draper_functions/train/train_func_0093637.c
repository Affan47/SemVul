asd_dump_frame_rcvd(struct asd_phy *phy,
			 struct done_list_struct *dl)
{
	unsigned long flags;
	int i;

	switch ((dl->status_block[1] & 0x70) >> 3) {
	case SAS_PROTOCOL_STP:
		ASD_DPRINTK("STP proto device-to-host FIS:\n");
		break;
	default:
	case SAS_PROTOCOL_SSP:
		ASD_DPRINTK("SAS proto IDENTIFY:\n");
		break;
	}
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	for (i = 0; i < phy->sas_phy.frame_rcvd_size; i+=4)
		ASD_DPRINTK("%02x: %02x %02x %02x %02x\n",
			    i,
			    phy->frame_rcvd[i],
			    phy->frame_rcvd[i+1],
			    phy->frame_rcvd[i+2],
			    phy->frame_rcvd[i+3]);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
}
