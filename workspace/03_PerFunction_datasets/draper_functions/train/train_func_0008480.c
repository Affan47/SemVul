pcm1792a_writeable_reg(struct device *dev, unsigned register reg)
{
	bool accessible;

	accessible = pcm1792a_accessible_reg(dev, reg);

	return accessible && reg != 0x16 && reg != 0x17;
}
