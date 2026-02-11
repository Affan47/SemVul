maybe_change_selected_wing_ship(int wb_num, int ws_num)
{
	Assert(wb_num >= 0 && wb_num < MAX_WING_BLOCKS);
	Assert(ws_num >= 0 && ws_num < MAX_WING_SLOTS);
	Assert( (Ss_wings != NULL) && (Wss_slots != NULL) );

	if ( Ss_wings[wb_num].wingnum < 0 ) {
		return;
	}

	if ( Selected_ss_class != -1 && Selected_ss_class != Wss_slots[wb_num*MAX_WING_SLOTS+ws_num].ship_class ) {
		Selected_ss_class = Wss_slots[wb_num*MAX_WING_SLOTS+ws_num].ship_class;
		start_ship_animation(Selected_ss_class, 1);
	}
}
