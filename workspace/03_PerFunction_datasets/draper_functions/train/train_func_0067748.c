barracks_set_callsign_enter_mode(bool set_callsign_enter_mode)
{

	Barracks_callsign_enter_mode = set_callsign_enter_mode;


	for (int idx=0; idx<BARRACKS_NUM_BUTTONS; idx++) {

		if((idx != B_SQUAD_PREV_BUTTON) && (idx != B_SQUAD_NEXT_BUTTON)){
			Buttons[gr_screen.res][idx].button.enable(!set_callsign_enter_mode);
		}
	}


	barracks_set_hotkeys(!set_callsign_enter_mode);

	Inputbox.enable(set_callsign_enter_mode);

	Inputbox.hide(!set_callsign_enter_mode);
}
