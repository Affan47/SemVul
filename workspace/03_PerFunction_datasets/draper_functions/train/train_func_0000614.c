dht_is_subvol_filled (xlator_t *this, xlator_t *subvol)
{
	int         i = 0;
	dht_conf_t *conf = NULL;
	gf_boolean_t subvol_filled_inodes = _gf_false;
	gf_boolean_t subvol_filled_space = _gf_false;
	gf_boolean_t is_subvol_filled = _gf_false;

	conf = this->private;


	LOCK (&conf->subvolume_lock);
	{
		for (i = 0; i < conf->subvolume_cnt; i++) {
			if (subvol == conf->subvolumes[i]) {
				if (conf->disk_unit == 'p') {
					if (conf->du_stats[i].avail_percent <
					    conf->min_free_disk) {
						subvol_filled_space = _gf_true;
						break;
					}

				} else {
					if (conf->du_stats[i].avail_space <
					    conf->min_free_disk) {
						subvol_filled_space = _gf_true;
						break;
					}
				}
				if (conf->du_stats[i].avail_inodes <
				    conf->min_free_inodes) {
					subvol_filled_inodes = _gf_true;
					break;
				}
			}
		}
	}
	UNLOCK (&conf->subvolume_lock);

	if (subvol_filled_space && conf->subvolume_status[i]) {
		if (!(conf->du_stats[i].log++ % (GF_UNIVERSAL_ANSWER * 10))) {
			gf_log (this->name, GF_LOG_WARNING,
				"disk space on subvolume '%s' is getting "
				"full (%.2f %%), consider adding more nodes",
				subvol->name,
				(100 - conf->du_stats[i].avail_percent));
		}
	}

	if (subvol_filled_inodes && conf->subvolume_status[i]) {
		if (!(conf->du_stats[i].log++ % (GF_UNIVERSAL_ANSWER * 10))) {
			gf_log (this->name, GF_LOG_CRITICAL,
				"inodes on subvolume '%s' are at "
				"(%.2f %%), consider adding more nodes",
				subvol->name,
				(100 - conf->du_stats[i].avail_inodes));
		}
	}

	is_subvol_filled = (subvol_filled_space || subvol_filled_inodes);

	return is_subvol_filled;
}
