_destroy_bg_config(bg_config_t *bg_conf)
{
	if (bg_conf) {
		if (bg_conf->blrts_list) {
			list_destroy(bg_conf->blrts_list);
			bg_conf->blrts_list = NULL;
		}

		xfree(bg_conf->bridge_api_file);

		xfree(bg_conf->default_blrtsimage);
		xfree(bg_conf->default_linuximage);
		xfree(bg_conf->default_mloaderimage);
		xfree(bg_conf->default_ramdiskimage);

		if (bg_conf->linux_list) {
			list_destroy(bg_conf->linux_list);
			bg_conf->linux_list = NULL;
		}

		if (bg_conf->mloader_list) {
			list_destroy(bg_conf->mloader_list);
			bg_conf->mloader_list = NULL;
		}

		if (bg_conf->ramdisk_list) {
			list_destroy(bg_conf->ramdisk_list);
			bg_conf->ramdisk_list = NULL;
		}

		FREE_NULL_BITMAP(bg_conf->reboot_qos_bitmap);
		xfree(bg_conf->slurm_user_name);
		xfree(bg_conf->slurm_node_prefix);
		xfree(bg_conf);
	}
}
