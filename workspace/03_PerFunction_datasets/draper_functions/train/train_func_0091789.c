mission_hotkey_set_defaults()
{
	int		i,j;
	wing		*wp;
	ship		*sp;
	object	*A;

	for ( i = 0; i < MAX_KEYED_TARGETS; i++ ) {
		hud_target_hotkey_clear(i);
	}


	Hotkey_sets_saved = 0;
	Mission_hotkey_save_timestamp = timestamp(HOTKEY_SAVE_TIME);


	if ( Num_hotkeys_saved > 0 ) {
		mission_hotkey_maybe_restore();
		return;
	}


	obj_merge_created_list();
	for ( A = GET_FIRST(&obj_used_list); A !=END_OF_LIST(&obj_used_list); A = GET_NEXT(A) ) {

		if ( (A == &obj_used_list) || (A->type != OBJ_SHIP) || ((Game_mode & GM_NORMAL) && (A == Player_obj)) ) {
			continue;
		}

		Assert(A->instance >= 0 && A->instance < MAX_SHIPS);
		sp = &Ships[A->instance];

		if ( sp->hotkey == -1 )
			continue;


		if ( sp->hotkey == MAX_KEYED_TARGETS )
			continue;

		Assert(sp->objnum >= 0);
		hud_target_hotkey_add_remove( sp->hotkey, &Objects[sp->objnum], HOTKEY_MISSION_FILE_ADDED );
	}


	for ( i = 0; i < Num_wings; i++ ) {
		wp = &Wings[i];

		if ( wp->hotkey == -1 )
			continue;


		if ( wp->hotkey == MAX_KEYED_TARGETS )
			continue;

		for ( j = 0; j < wp->current_count; j++ ) {
			if ( wp->ship_index[j] == -1 )
				continue;

			sp = &Ships[wp->ship_index[j]];
			hud_target_hotkey_add_remove( wp->hotkey, &Objects[sp->objnum], HOTKEY_MISSION_FILE_ADDED );
		}
	}
}
