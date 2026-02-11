ai_maybe_self_destruct(object *objp, ai_info *aip)
{


	if ((Iff_info[Ships[objp->instance].team].flags & IFFF_SUPPORT_ALLOWED) || (Game_mode & GM_MULTIPLAYER))
		return;


	if ((Ship_info[Ships[objp->instance].ship_info_index].flags & SIF_SMALL_SHIP) && (Ships[objp->instance].wingnum != -1)) {
		if ((ship_get_subsystem_strength(&Ships[objp->instance], SUBSYSTEM_ENGINE) <= 0.0f) ||
			(ship_get_subsystem_strength(&Ships[objp->instance], SUBSYSTEM_WEAPONS) <= 0.0f)) {
			if (aip->self_destruct_timestamp < 0)
				aip->self_destruct_timestamp = timestamp(90 * 1000);
		} else {
			aip->self_destruct_timestamp = -1;
		}

		if (aip->self_destruct_timestamp < 0) {
			return;
		}

		if (timestamp_elapsed(aip->self_destruct_timestamp)) {
			ship_apply_local_damage( objp, objp, &objp->pos, objp->hull_strength*flFrametime + 1.0f, MISS_SHIELDS);
		}
	}
}
