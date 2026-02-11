wm_coeff_init_control_caches(struct wm_adsp *dsp)
{
	struct wm_coeff_ctl *ctl;
	int ret;

	list_for_each_entry(ctl, &dsp->ctl_list, list) {
		if (!ctl->enabled || ctl->set)
			continue;
		if (ctl->flags & WMFW_CTL_FLAG_VOLATILE)
			continue;

		ret = wm_coeff_read_control(ctl,
					    ctl->cache,
					    ctl->len);
		if (ret < 0)
			return ret;
	}

	return 0;
}
