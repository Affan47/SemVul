hud_target_hotkey_select( int k )
{
	int visible_count = 0;
	htarget_list *hitem, *plist, *target, *next_target, *first_target;
	int target_objnum;

	plist = &(Players[Player_num].keyed_targets[k]);

	if ( EMPTY( plist ) )
		return;


	for ( hitem = GET_FIRST(plist); hitem != END_OF_LIST(plist); hitem = GET_NEXT(hitem) ){
		if (awacs_get_level(hitem->objp, Player_ship, 1) > 1) {
			visible_count++;
		}
	}


	if (visible_count == 0) {
		return;
	}


	target_objnum = Player_ai->target_objnum;
	target = NULL;
	next_target = NULL;
	first_target = NULL;
	for ( hitem = GET_FIRST(plist); hitem != END_OF_LIST(plist); hitem = GET_NEXT(hitem) ) {

		if (awacs_get_level(hitem->objp, Player_ship, 1) > 1) {

			if (first_target == NULL) {
				first_target = hitem;
			}


			if (target != NULL) {
				next_target = hitem;
				break;
			}
		}


		if ( OBJ_INDEX(hitem->objp) == target_objnum ) {
			target = hitem;
		}
	}


	if (target == NULL) {
		Assert(first_target != NULL);
		if (first_target != NULL) {
			target = first_target;
			next_target = first_target;
		} else {

			return;
		}


	} else if (Players[Player_num].current_hotkey_set != k) {
		next_target = target;
	}


	if (visible_count > 1) {

		if (next_target != NULL) {
			target = next_target;
		} else {


			for ( hitem = GET_FIRST(plist); hitem != END_OF_LIST(plist); hitem = GET_NEXT(hitem) ) {
				if (awacs_get_level(hitem->objp, Player_ship, 1) > 1) {
					target = hitem;
					break;
				}
			}
		}
	}

	Assert( target != END_OF_LIST(plist) );

	if ( Player_obj != target->objp ){
		set_target_objnum( Player_ai, OBJ_INDEX(target->objp) );
	}

	Players[Player_num].current_hotkey_set = k;
}
