wl_set_selected_slot(int slot_num)
{
	Selected_wl_slot = slot_num;
	if ( Selected_wl_slot >= 0 ) {
		Assert( Wss_slots != NULL );
		wl_set_disabled_weapons(Wss_slots[slot_num].ship_class);
	}
}
