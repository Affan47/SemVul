set_ac97_input(struct em28xx *dev)
{
	int ret, i;
	enum em28xx_amux amux = dev->ctl_ainput;


	if (amux == EM28XX_AMUX_VIDEO2)
		amux = EM28XX_AMUX_VIDEO;


	for (i = 0; i < ARRAY_SIZE(inputs); i++) {
		if (amux == inputs[i].mux)
			ret = em28xx_write_ac97(dev, inputs[i].reg, 0x0808);
		else
			ret = em28xx_write_ac97(dev, inputs[i].reg, 0x8000);

		if (ret < 0)
			em28xx_warn("couldn't setup AC97 register %d\n",
				    inputs[i].reg);
	}
	return 0;
}
