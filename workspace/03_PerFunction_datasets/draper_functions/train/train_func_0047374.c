vg_set_clustered(struct volume_group *vg, int clustered)
{
	struct lv_list *lvl;


	dm_list_iterate_items(lvl, &vg->lvs) {


		if (lv_is_raid_type(lvl->lv)) {
			log_error("RAID logical volumes are not allowed "
				  "in a cluster volume group.");
			return 0;
		}

		if (lv_is_active(lvl->lv) &&
		    (lv_is_mirrored(lvl->lv) || lv_is_raid_type(lvl->lv))) {
			log_error("%s logical volumes must be inactive "
				  "when changing the cluster attribute.",
				  lv_is_raid_type(lvl->lv) ? "RAID" : "Mirror");
			return 0;
		}

		if (clustered) {
			if (lv_is_origin(lvl->lv) || lv_is_cow(lvl->lv)) {
				log_error("Volume group %s contains snapshots "
					  "that are not yet supported.",
					  vg->name);
				return 0;
			}
		}

		if ((lv_is_origin(lvl->lv) || lv_is_cow(lvl->lv)) &&
		    lv_is_active(lvl->lv)) {
			log_error("Snapshot logical volumes must be inactive "
				  "when changing the cluster attribute.");
			return 0;
		}
	}

	if (clustered)
		vg->status |= CLUSTERED;
	else
		vg->status &= ~CLUSTERED;
	return 1;
}
