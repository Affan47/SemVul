ata_sff_data_xfer32(struct ata_device *dev, unsigned char *buf,
			       unsigned int buflen, int rw)
{
	struct ata_port *ap = dev->link->ap;
	void __iomem *data_addr = ap->ioaddr.data_addr;
	unsigned int words = buflen >> 2;
	int slop = buflen & 3;

	if (!(ap->pflags & ATA_PFLAG_PIO32))
		return ata_sff_data_xfer(dev, buf, buflen, rw);


	if (rw == READ)
		ioread32_rep(data_addr, buf, words);
	else
		iowrite32_rep(data_addr, buf, words);


	if (unlikely(slop)) {
		unsigned char pad[4] = { };


		buf += buflen - slop;


		if (rw == READ) {
			if (slop < 3)
				ioread16_rep(data_addr, pad, 1);
			else
				ioread32_rep(data_addr, pad, 1);
			memcpy(buf, pad, slop);
		} else {
			memcpy(pad, buf, slop);
			if (slop < 3)
				iowrite16_rep(data_addr, pad, 1);
			else
				iowrite32_rep(data_addr, pad, 1);
		}
	}
	return (buflen + 1) & ~1;
}
