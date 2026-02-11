tpm_atml_send(struct tpm_chip *chip, u8 *buf, size_t count)
{
	int i;

	dev_dbg(&chip->dev, "tpm_atml_send:\n");
	for (i = 0; i < count; i++) {
		dev_dbg(&chip->dev, "%d 0x%x(%d)\n",  i, buf[i], buf[i]);
 		iowrite8(buf[i], chip->vendor.iobase);
	}

	return count;
}
