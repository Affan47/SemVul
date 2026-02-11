free_tag(struct DeviceCtlBlk *dcb, struct ScsiReqBlk *srb)
{
	if (srb->tag_number < 255) {
		dcb->tag_mask &= ~(1 << srb->tag_number);
		srb->tag_number = 255;
	}
}
