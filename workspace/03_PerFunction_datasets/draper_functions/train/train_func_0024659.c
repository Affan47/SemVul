_text_lv_setup(struct format_instance *fid __attribute__((unused)),
			  struct logical_volume *lv)
{


	if (!*lv->lvid.s && !lvid_create(&lv->lvid, &lv->vg->id)) {
		log_error("Random lvid creation failed for %s/%s.",
			  lv->vg->name, lv->name);
		return 0;
	}

	return 1;
}
