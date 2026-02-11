pdc20621_ata_pkt(struct ata_taskfile *tf,
					    unsigned int devno, u8 *buf,
					    unsigned int portno)
{
	unsigned int i, dw;
	__le32 *buf32 = (__le32 *) buf;
	u8 dev_reg;

	unsigned int dimm_sg = PDC_20621_DIMM_BASE +
			       (PDC_DIMM_WINDOW_STEP * portno) +
			       PDC_DIMM_APKT_PRD;
	VPRINTK("ENTER, dimm_sg == 0x%x, %d\n", dimm_sg, dimm_sg);

	i = PDC_DIMM_ATA_PKT;


	if ((tf->protocol == ATA_PROT_DMA) && (!(tf->flags & ATA_TFLAG_WRITE)))
		buf[i++] = PDC_PKT_READ;
	else if (tf->protocol == ATA_PROT_NODATA)
		buf[i++] = PDC_PKT_NODATA;
	else
		buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = portno + 1;
	buf[i++] = 0xff;


	dw = i >> 2;
	if (tf->protocol == ATA_PROT_NODATA)
		buf32[dw] = 0;
	else
		buf32[dw] = cpu_to_le32(dimm_sg);
	buf32[dw + 1] = 0;
	i += 8;

	if (devno == 0)
		dev_reg = ATA_DEVICE_OBS;
	else
		dev_reg = ATA_DEVICE_OBS | ATA_DEV1;


	buf[i++] = (1 << 5) | PDC_PKT_CLEAR_BSY | ATA_REG_DEVICE;
	buf[i++] = dev_reg;


	buf[i++] = (1 << 5) | PDC_REG_DEVCTL;
	buf[i++] = tf->ctl;

	return i;
}
