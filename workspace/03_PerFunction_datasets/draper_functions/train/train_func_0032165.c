wm8958_dsp_apply(struct snd_soc_codec *codec, int path, int start)
{
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);
	int pwr_reg = snd_soc_read(codec, WM8994_POWER_MANAGEMENT_5);
	int ena, reg, aif;

	switch (path) {
	case 0:
		pwr_reg &= (WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC1R_ENA);
		aif = 0;
		break;
	case 1:
		pwr_reg &= (WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA);
		aif = 0;
		break;
	case 2:
		pwr_reg &= (WM8994_AIF2DACL_ENA | WM8994_AIF2DACR_ENA);
		aif = 1;
		break;
	default:
		WARN(1, "Invalid path %d\n", path);
		return;
	}


	ena = wm8994->mbc_ena[path] || wm8994->vss_ena[path] ||
		wm8994->hpf1_ena[path] || wm8994->hpf2_ena[path] ||
		wm8994->enh_eq_ena[path];
	if (!pwr_reg)
		ena = 0;

	reg = snd_soc_read(codec, WM8958_DSP2_PROGRAM);

	dev_dbg(codec->dev, "DSP path %d %d startup: %d, power: %x, DSP: %x\n",
		path, wm8994->dsp_active, start, pwr_reg, reg);

	if (start && ena) {

		if (reg & WM8958_DSP2_ENA)
			return;


		if (!(snd_soc_read(codec, WM8994_AIF1_CLOCKING_1)
		      & WM8994_AIF1CLK_ENA_MASK) &&
		    !(snd_soc_read(codec, WM8994_AIF2_CLOCKING_1)
		      & WM8994_AIF2CLK_ENA_MASK))
			return;


		snd_soc_update_bits(codec, WM8994_CLOCKING_1,
				    WM8958_DSP2CLK_SRC | WM8958_DSP2CLK_ENA,
				    aif << WM8958_DSP2CLK_SRC_SHIFT |
				    WM8958_DSP2CLK_ENA);

		if (wm8994->enh_eq_ena[path])
			wm8958_dsp_start_enh_eq(codec, path);
		else if (wm8994->vss_ena[path] || wm8994->hpf1_ena[path] ||
		    wm8994->hpf2_ena[path])
			wm8958_dsp_start_vss(codec, path);
		else if (wm8994->mbc_ena[path])
			wm8958_dsp_start_mbc(codec, path);

		wm8994->dsp_active = path;

		dev_dbg(codec->dev, "DSP running in path %d\n", path);
	}

	if (!start && wm8994->dsp_active == path) {

		if (!(reg & WM8958_DSP2_ENA))
			return;

		snd_soc_update_bits(codec, WM8958_DSP2_CONFIG,
				    WM8958_MBC_ENA, 0);
		snd_soc_write(codec, WM8958_DSP2_EXECCONTROL,
			      WM8958_DSP2_STOP);
		snd_soc_update_bits(codec, WM8958_DSP2_PROGRAM,
				    WM8958_DSP2_ENA, 0);
		snd_soc_update_bits(codec, WM8994_CLOCKING_1,
				    WM8958_DSP2CLK_ENA, 0);

		wm8994->dsp_active = -1;

		dev_dbg(codec->dev, "DSP stopped\n");
	}
}
