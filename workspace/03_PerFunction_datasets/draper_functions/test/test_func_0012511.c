ppa_out(ppa_struct *dev, char *buffer, int len)
{
	int r;
	unsigned short ppb = dev->base;

	r = ppa_wait(dev);

	if ((r & 0x50) != 0x40) {
		ppa_fail(dev, DID_ERROR);
		return 0;
	}
	switch (dev->mode) {
	case PPA_NIBBLE:
	case PPA_PS2:

		r = ppa_byte_out(ppb, buffer, len);
		break;

	case PPA_EPP_32:
	case PPA_EPP_16:
	case PPA_EPP_8:
		epp_reset(ppb);
		w_ctr(ppb, 0x4);
#ifdef CONFIG_SCSI_IZIP_EPP16
		if (!(((long) buffer | len) & 0x01))
			outsw(ppb + 4, buffer, len >> 1);
#else
		if (!(((long) buffer | len) & 0x03))
			outsl(ppb + 4, buffer, len >> 2);
#endif
		else
			outsb(ppb + 4, buffer, len);
		w_ctr(ppb, 0xc);
		r = !(r_str(ppb) & 0x01);
		w_ctr(ppb, 0xc);
		ecp_sync(dev);
		break;

	default:
		printk(KERN_ERR "PPA: bug in ppa_out()\n");
		r = 0;
	}
	return r;
}
