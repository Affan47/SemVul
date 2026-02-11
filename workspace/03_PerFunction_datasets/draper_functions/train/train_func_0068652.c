scarlett_ctl_enum_dynamic_info(struct snd_kcontrol *kctl,
					  struct snd_ctl_elem_info *uinfo)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct scarlett_mixer_elem_enum_info *opt = elem->private_data;
	unsigned int items = opt->len;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = elem->channels;
	uinfo->value.enumerated.items = items;

	if (uinfo->value.enumerated.item >= items)
		uinfo->value.enumerated.item = items - 1;


	scarlett_generate_name(uinfo->value.enumerated.item,
			       uinfo->value.enumerated.name,
			       opt->offsets);

	return 0;
}
