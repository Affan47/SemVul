hud_wingman_status_update()
{
	if ( timestamp_elapsed(HUD_wingman_update_timer) ) {
		int		wing_index,wing_pos;
		ship_obj	*so;
		object	*ship_objp;
		ship		*shipp;

		HUD_wingman_update_timer=timestamp(HUD_WINGMAN_UPDATE_STATUS_INTERVAL);

		for ( so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so) ) {
			ship_objp = &Objects[so->objnum];
			shipp = &Ships[ship_objp->instance];

			wing_index = shipp->wing_status_wing_index;
			wing_pos = shipp->wing_status_wing_pos;

			if ( (wing_index >= 0) && (wing_pos >= 0) && !(ship_objp->flags & OF_SHOULD_BE_DEAD) ) {

				HUD_wingman_status[wing_index].used = 1;
				if (!(shipp->flags & SF_DEPARTING) ) {
					HUD_wingman_status[wing_index].status[wing_pos] = HUD_WINGMAN_STATUS_ALIVE;
				}
				HUD_wingman_status[wing_index].hull[wing_pos] = get_hull_pct(ship_objp);
				if ( HUD_wingman_status[wing_index].hull[wing_pos] <= 0 ) {
					HUD_wingman_status[wing_index].status[wing_pos] = HUD_WINGMAN_STATUS_DEAD;
				}
			}
		}
	}
}
