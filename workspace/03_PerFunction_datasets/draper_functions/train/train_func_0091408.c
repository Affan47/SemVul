drop_icon_on_slot(int bank_num)
{
	if ( Selected_wl_slot == -1 ) {
		return 0;
	}

	if(Game_mode & GM_MULTIPLAYER){
		if(multi_ts_disabled_slot(Selected_wl_slot)){
			return 0;
		}
	} else {
		if ( ss_disabled_slot( Selected_wl_slot, false ) ){
			return 0;
		}
	}

	Assert( Wss_slots != NULL );


	if ( Wss_slots[Selected_wl_slot].wep_count[bank_num] < 0 ) {
		return 0;
	}

	if ( !wl_carried_icon_moved() ) {
		wl_reset_carried_icon();
		return 0;
	}

	wl_drop(Carried_wl_icon.from_bank, Carried_wl_icon.weapon_class, bank_num, -1, Selected_wl_slot);
	return 1;
}
