add_card(struct hint_list *list, int card)
{
	int err, ok;
	snd_config_t *conf, *n;
	snd_config_iterator_t i, next;
	const char *str;
	char ctl_name[16];
	snd_ctl_card_info_t *info;
	int device, max_device = 0;

	snd_ctl_card_info_alloca(&info);
	list->info = info;
	err = snd_config_search(snd_config, list->siface, &conf);
	if (err < 0)
		return err;
	sprintf(ctl_name, "hw:%i", card);
	err = snd_ctl_open(&list->ctl, ctl_name, 0);
	if (err < 0)
		return err;
	err = snd_ctl_card_info(list->ctl, info);
	if (err < 0)
		goto __error;
	snd_config_for_each(i, next, conf) {
		n = snd_config_iterator_entry(i);
		if (snd_config_get_id(n, &str) < 0)
			continue;

		if (next_devices[list->iface] != NULL) {
			list->card = card;
			device = max_device = -1;
			err = next_devices[list->iface](list->ctl, &device);
			if (device < 0)
				err = -EINVAL;
			else
				max_device = device;
			while (err >= 0 && device >= 0) {
				err = next_devices[list->iface](list->ctl, &device);
				if (err >= 0 && device > max_device)
					max_device = device;
			}
			ok = 0;
			for (device = 0; err >= 0 && device <= max_device; device++) {
				list->device = device;
				err = try_config(list, list->siface, str);
				if (err < 0)
					break;
				ok++;
			}
			if (ok)
				continue;
		} else {
			err = -EINVAL;
		}
		if (err == -EXDEV)
			continue;
		if (err < 0) {
			list->card = card;
			list->device = -1;
			err = try_config(list, list->siface, str);
		}
		if (err == -ENOMEM)
			goto __error;
	}
	err = 0;
      __error:
      	snd_ctl_close(list->ctl);
	return err;
}
