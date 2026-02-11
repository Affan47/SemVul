hdmi_chmap_ctl_tlv(struct snd_kcontrol *kcontrol, int op_flag,
			      unsigned int size, unsigned int __user *tlv)
{
	struct snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	struct hda_codec *codec = info->private_data;
	struct hdmi_spec *spec = codec->spec;
	unsigned int __user *dst;
	int chs, count = 0;

	if (size < 8)
		return -ENOMEM;
	if (put_user(SNDRV_CTL_TLVT_CONTAINER, tlv))
		return -EFAULT;
	size -= 8;
	dst = tlv + 2;
	for (chs = 2; chs <= spec->channels_max; chs++) {
		int i;
		struct cea_channel_speaker_allocation *cap;
		cap = channel_allocations;
		for (i = 0; i < ARRAY_SIZE(channel_allocations); i++, cap++) {
			int chs_bytes = chs * 4;
			int type = spec->ops.chmap_cea_alloc_validate_get_type(cap, chs);
			unsigned int tlv_chmap[8];

			if (type < 0)
				continue;
			if (size < 8)
				return -ENOMEM;
			if (put_user(type, dst) ||
			    put_user(chs_bytes, dst + 1))
				return -EFAULT;
			dst += 2;
			size -= 8;
			count += 8;
			if (size < chs_bytes)
				return -ENOMEM;
			size -= chs_bytes;
			count += chs_bytes;
			spec->ops.cea_alloc_to_tlv_chmap(cap, tlv_chmap, chs);
			if (copy_to_user(dst, tlv_chmap, chs_bytes))
				return -EFAULT;
			dst += chs;
		}
	}
	if (put_user(count, tlv + 1))
		return -EFAULT;
	return 0;
}
