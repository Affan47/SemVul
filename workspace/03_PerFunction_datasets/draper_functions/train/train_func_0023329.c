hdmi_create_eld_ctl(struct hda_codec *codec, int pin_idx,
			int device)
{
	struct snd_kcontrol *kctl;
	struct hdmi_spec *spec = codec->spec;
	int err;

	kctl = snd_ctl_new1(&eld_bytes_ctl, codec);
	if (!kctl)
		return -ENOMEM;
	kctl->private_value = pin_idx;
	kctl->id.device = device;

	err = snd_hda_ctl_add(codec, get_pin(spec, pin_idx)->pin_nid, kctl);
	if (err < 0)
		return err;

	get_pin(spec, pin_idx)->eld_ctl = kctl;
	return 0;
}
