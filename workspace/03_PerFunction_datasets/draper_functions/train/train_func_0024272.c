fsl_asoc_card_audmux_init(struct device_node *np,
				     struct fsl_asoc_card_priv *priv)
{
	struct device *dev = &priv->pdev->dev;
	u32 int_ptcr = 0, ext_ptcr = 0;
	int int_port, ext_port;
	int ret;

	ret = of_property_read_u32(np, "mux-int-port", &int_port);
	if (ret) {
		dev_err(dev, "mux-int-port missing or invalid\n");
		return ret;
	}
	ret = of_property_read_u32(np, "mux-ext-port", &ext_port);
	if (ret) {
		dev_err(dev, "mux-ext-port missing or invalid\n");
		return ret;
	}


	int_port--;
	ext_port--;


	switch (priv->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		int_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_RFSDIR |
			   IMX_AUDMUX_V2_PTCR_RCLKDIR |
			   IMX_AUDMUX_V2_PTCR_TFSDIR |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		break;
	default:
		if (!fsl_asoc_card_is_ac97(priv))
			return -EINVAL;
	}

	if (fsl_asoc_card_is_ac97(priv)) {
		int_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCLKDIR;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TFSEL(int_port) |
			   IMX_AUDMUX_V2_PTCR_TFSDIR;
	}


	if (!fsl_asoc_card_is_ac97(priv)) {
		unsigned int pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port);

		ret = imx_audmux_v2_configure_port(int_port, 0,
						   pdcr);
		if (ret) {
			dev_err(dev, "audmux internal port setup failed\n");
			return ret;
		}
	}

	ret = imx_audmux_v2_configure_port(int_port, int_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port));
	if (ret) {
		dev_err(dev, "audmux internal port setup failed\n");
		return ret;
	}

	if (!fsl_asoc_card_is_ac97(priv)) {
		unsigned int pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(int_port);

		ret = imx_audmux_v2_configure_port(ext_port, 0,
						   pdcr);
		if (ret) {
			dev_err(dev, "audmux external port setup failed\n");
			return ret;
		}
	}

	ret = imx_audmux_v2_configure_port(ext_port, ext_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(int_port));
	if (ret) {
		dev_err(dev, "audmux external port setup failed\n");
		return ret;
	}

	return 0;
}
