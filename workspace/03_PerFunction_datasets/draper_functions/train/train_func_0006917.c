ai_post_process_mission()
{
	object *objp;
	int i;


	if ( !Fred_running ) {


		for ( i = 0; i < MAX_STARTING_WINGS; i++ ) {
			if ( Starting_wings[i] == Player_ship->wingnum ) {
				wing *wingp;

				wingp = &Wings[Starting_wings[i]];

				ai_maybe_add_form_goal( wingp );

			}
		}
	}


	for ( objp = GET_FIRST(&obj_used_list); objp != END_OF_LIST(&obj_used_list); objp = GET_NEXT(objp) ) {
		if ( objp->type != OBJ_SHIP )
			continue;
		ai_process_mission_orders( OBJ_INDEX(objp), &Ai_info[Ships[objp->instance].ai_index] );
	}
	for ( objp = GET_FIRST(&obj_create_list); objp != END_OF_LIST(&obj_create_list); objp = GET_NEXT(objp) ) {
		if ( (objp->type != OBJ_SHIP) || Fred_running )
			continue;
		ai_process_mission_orders( OBJ_INDEX(objp), &Ai_info[Ships[objp->instance].ai_index] );
	}

	return;
}
