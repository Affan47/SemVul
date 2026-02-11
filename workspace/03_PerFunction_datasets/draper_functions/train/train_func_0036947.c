ai_do_repair_frame(object *objp, ai_info *aip, float frametime)
{
	static bool rearm_eta_found=false;

	if (Ships[objp->instance].team == Iff_traitor) {
		ai_abort_rearm_request(objp);
		return;
	}

	if (aip->ai_flags & (AIF_BEING_REPAIRED | AIF_AWAITING_REPAIR)) {
		int	support_objnum;

		ai_info	*repair_aip;

		support_objnum = aip->support_ship_objnum;

		if (support_objnum == -1)
			return;


		Assert(Objects[support_objnum].signature == aip->support_ship_signature);

		repair_aip = &Ai_info[Ships[Objects[support_objnum].instance].ai_index];

		if (aip->ai_flags & AIF_BEING_REPAIRED) {


			if (Missiontime - repair_aip->submode_start_time > REARM_SOUND_DELAY) {
				int repaired;

				if (!rearm_eta_found && objp==Player_obj && Player_rearm_eta <= 0)
				{
					rearm_eta_found = true;
					Player_rearm_eta = ship_calculate_rearm_duration(objp);
				}

				repaired = ship_do_rearm_frame( objp, frametime );


				if ( repaired && (repair_aip->submode == AIS_DOCK_4)) {

					repair_aip->submode = AIS_UNDOCK_0;
					repair_aip->submode_start_time = Missiontime;


					if ( !MULTIPLAYER_CLIENT ) {
						ai_do_objects_repairing_stuff( objp, &Objects[support_objnum], REPAIR_INFO_COMPLETE );
					}
				}
			}
		} else if (aip->ai_flags & AIF_AWAITING_REPAIR) {

			if ( !MULTIPLAYER_CLIENT ) {
				if ((Game_mode & GM_MULTIPLAYER) || (objp != Player_obj)) {
					if ((repair_aip->goal_objnum == OBJ_INDEX(objp)) && (timestamp_elapsed(aip->abort_rearm_timestamp))) {
						ai_abort_rearm_request(objp);
						aip->next_rearm_request_timestamp = timestamp(NEXT_REARM_TIMESTAMP);
					}
				}
			}
		}
	} else {


		if ( objp == Player_obj ) {
			Player_rearm_eta = 0;
			rearm_eta_found = false;
			player_stop_repair_sound();
		}
	}
}
