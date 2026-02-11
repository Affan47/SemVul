hud_target_in_reticle_old()
{
	object	*A, *target_obj;
	float	dot;
	vec3d	vec_to_target;

	for ( A = GET_FIRST(&obj_used_list); A !=END_OF_LIST(&obj_used_list); A = GET_NEXT(A) ) {
		if ( !object_targetable_in_reticle(A) ) {
			continue;
		}

		if ( A->type == OBJ_WEAPON ) {
			if ( !(Weapon_info[Weapons[A->instance].weapon_info_index].wi_flags2 & WIF2_CAN_BE_TARGETED) ){
				if ( !(Weapon_info[Weapons[A->instance].weapon_info_index].wi_flags & WIF_BOMB) ){
					continue;
				}
			}

			if (Weapons[A->instance].lssm_stage==3){
				continue;
			}
		}

		if ( A->type == OBJ_SHIP ) {
			if ( Ships[A->instance].flags & TARGET_SHIP_IGNORE_FLAGS ){
				continue;
			}
		}

		if(hud_target_invalid_awacs(A)){
			continue;
		}

		if ( vm_vec_same( &A->pos, &Eye_position ) ) {
			continue;
		}

		vm_vec_normalized_dir(&vec_to_target, &A->pos, &Eye_position);
		dot = vm_vec_dot(&Player_obj->orient.vec.fvec, &vec_to_target);

		if ( dot > MIN_DOT_FOR_TARGET ) {
			hud_reticle_list_update(A, dot, 1);
		}
	}

	target_obj = hud_reticle_pick_target();
	if ( target_obj != NULL ) {
		set_target_objnum( Player_ai, OBJ_INDEX(target_obj) );
		if ( target_obj->type == OBJ_SHIP ) {

			hud_maybe_set_sorted_turret_subsys(&Ships[target_obj->instance]);
			hud_restore_subsystem_target(&Ships[target_obj->instance]);
		}
	}
	else {
			snd_play( &Snds[SND_TARGET_FAIL], 0.0f );
	}
}
