_clear_lv(struct logical_volume *lv)
{
	int was_active = lv_is_active(lv);

	if (test_mode())
		return 1;

	if (!was_active && !activate_lv(lv->vg->cmd, lv)) {
		log_error("Failed to activate %s for clearing",
			  lv->name);
		return 0;
	}

	log_verbose("Clearing metadata area of %s/%s",
		    lv->vg->name, lv->name);


	if (!set_lv(lv->vg->cmd, lv, 1, 0)) {
		log_error("Failed to zero %s", lv->name);
		return 0;
	}

	if (!was_active && !deactivate_lv(lv->vg->cmd, lv)) {
		log_error("Failed to deactivate %s", lv->name);
		return 0;
	}

	return 1;
}
