hvr950q_cs5340_audio(void *priv, int enable)
{


	struct au0828_dev *dev = priv;
	if (enable == 1)
		au0828_set(dev, REG_000, 0x10);
	else
		au0828_clear(dev, REG_000, 0x10);
}
