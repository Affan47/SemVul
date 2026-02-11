patch_tegra_hdmi(struct hda_codec *codec)
{
	int err;

	err = patch_generic_hdmi(codec);
	if (err)
		return err;

	codec->patch_ops.build_pcms = tegra_hdmi_build_pcms;

	return 0;
}
