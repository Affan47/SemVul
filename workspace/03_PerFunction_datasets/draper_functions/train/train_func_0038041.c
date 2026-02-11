snd_func_pcm_id(snd_config_t **dst, snd_config_t *root, snd_config_t *src, void *private_data)
{
	snd_config_t *n;
	snd_ctl_t *ctl = NULL;
	snd_pcm_info_t *info;
	const char *id;
	long card, device, subdevice = 0;
	int err;

	card = parse_card(root, src, private_data);
	if (card < 0)
		return card;
	err = snd_config_search(src, "device", &n);
	if (err < 0) {
		SNDERR("field device not found");
		goto __error;
	}
	err = snd_config_evaluate(n, root, private_data, NULL);
	if (err < 0) {
		SNDERR("error evaluating device");
		goto __error;
	}
	err = snd_config_get_integer(n, &device);
	if (err < 0) {
		SNDERR("field device is not an integer");
		goto __error;
	}
	if (snd_config_search(src, "subdevice", &n) >= 0) {
		err = snd_config_evaluate(n, root, private_data, NULL);
		if (err < 0) {
			SNDERR("error evaluating subdevice");
			goto __error;
		}
		err = snd_config_get_integer(n, &subdevice);
		if (err < 0) {
			SNDERR("field subdevice is not an integer");
			goto __error;
		}
	}
	err = open_ctl(card, &ctl);
	if (err < 0) {
		SNDERR("could not open control for card %li", card);
		goto __error;
	}
	snd_pcm_info_alloca(&info);
	snd_pcm_info_set_device(info, device);
	snd_pcm_info_set_subdevice(info, subdevice);
	err = snd_ctl_pcm_info(ctl, info);
	if (err < 0) {
		SNDERR("snd_ctl_pcm_info error: %s", snd_strerror(err));
		goto __error;
	}
	err = snd_config_get_id(src, &id);
	if (err >= 0)
		err = snd_config_imake_string(dst, id, snd_pcm_info_get_id(info));
      __error:
      	if (ctl)
      		snd_ctl_close(ctl);
	return err;
}
