sh_csi2_hwinit(struct sh_csi2 *priv)
{
	struct sh_csi2_pdata *pdata = priv->pdev->dev.platform_data;
	__u32 tmp = 0x10;


	iowrite32(0x00000001, priv->base + SH_CSI2_TREF);

	iowrite32(0x00000001, priv->base + SH_CSI2_SRST);
	udelay(5);
	iowrite32(0x00000000, priv->base + SH_CSI2_SRST);

	switch (pdata->type) {
	case SH_CSI2C:
		if (priv->client->lanes == 1)
			tmp |= 1;
		else

			tmp |= 3;
		break;
	case SH_CSI2I:
		if (!priv->client->lanes || priv->client->lanes > 4)

			tmp |= 0xf;
		else
			tmp |= (1 << priv->client->lanes) - 1;
	}

	if (priv->client->phy == SH_CSI2_PHY_MAIN)
		tmp |= 0x8000;

	iowrite32(tmp, priv->base + SH_CSI2_PHYCNT);

	tmp = 0;
	if (pdata->flags & SH_CSI2_ECC)
		tmp |= 2;
	if (pdata->flags & SH_CSI2_CRC)
		tmp |= 1;
	iowrite32(tmp, priv->base + SH_CSI2_CHKSUM);
}
