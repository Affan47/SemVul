slurm_set_tree_width(uint16_t tree_width)
{
	slurm_ctl_conf_t *conf;

	if (slurmdbd_conf) {
	} else {
		conf = slurm_conf_lock();
		if (tree_width == 0) {
			error("can't have span count of 0");
			return SLURM_ERROR;
		}
		conf->tree_width = tree_width;
		slurm_conf_unlock();
	}
	return 0;
}
