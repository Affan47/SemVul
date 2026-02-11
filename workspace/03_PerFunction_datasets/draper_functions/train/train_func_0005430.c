crb_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct crb_priv *priv = chip->vendor.priv;
	unsigned int expected;


	if (count < 6)
		return -EIO;

	if (ioread32(&priv->cca->sts) & CRB_CA_STS_ERROR)
		return -EIO;

	memcpy_fromio(buf, priv->rsp, 6);
	expected = be32_to_cpup((__be32 *) &buf[2]);
	if (expected > count || expected < 6)
		return -EIO;

	memcpy_fromio(&buf[6], &priv->rsp[6], expected - 6);

	return expected;
}
