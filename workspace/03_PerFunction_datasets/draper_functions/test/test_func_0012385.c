pin_configs_show(struct hda_codec *codec,
				struct snd_array *list,
				char *buf)
{
	int i, len = 0;
	mutex_lock(&codec->user_mutex);
	for (i = 0; i < list->used; i++) {
		struct hda_pincfg *pin = snd_array_elem(list, i);
		len += sprintf(buf + len, "0x%02x 0x%08x\n",
			       pin->nid, pin->cfg);
	}
	mutex_unlock(&codec->user_mutex);
	return len;
}
