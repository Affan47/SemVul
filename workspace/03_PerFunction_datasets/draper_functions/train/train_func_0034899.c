saa7146_res_free(struct saa7146_fh *fh, unsigned int bits)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;

	BUG_ON((fh->resources & bits) != bits);

	fh->resources &= ~bits;
	vv->resources &= ~bits;
	DEB_D("res: put 0x%02x, cur:0x%02x\n", bits, vv->resources);
}
