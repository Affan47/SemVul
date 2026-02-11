mcam_set_config_needed(struct mcam_camera *cam, int needed)
{
	if (needed)
		set_bit(CF_CONFIG_NEEDED, &cam->flags);
	else
		clear_bit(CF_CONFIG_NEEDED, &cam->flags);
}
