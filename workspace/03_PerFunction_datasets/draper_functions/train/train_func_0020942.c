ad1980_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AC97_RESET ... AC97_MASTER_MONO:
	case AC97_PHONE ... AC97_CD:
	case AC97_AUX ... AC97_GENERAL_PURPOSE:
	case AC97_POWERDOWN ... AC97_PCM_LR_ADC_RATE:
	case AC97_SPDIF:
	case AC97_CODEC_CLASS_REV:
	case AC97_PCI_SVID:
	case AC97_AD_CODEC_CFG:
	case AC97_AD_JACK_SPDIF:
	case AC97_AD_SERIAL_CFG:
	case AC97_VENDOR_ID1:
	case AC97_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}
