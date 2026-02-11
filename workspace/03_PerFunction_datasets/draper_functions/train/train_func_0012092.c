hud_target_subsystem_in_reticle()
{
	object* targetp;
	ship_subsys	*subsys;
	ship_subsys *nearest_subsys = NULL;
	vec3d subobj_pos;

	float dot, best_dot;
	vec3d vec_to_target;
	best_dot = -1.0f;

	if ( Player_ai->target_objnum == -1){
		hud_target_in_reticle_old();
	}

	if ( Player_ai->target_objnum == -1) {
		snd_play( &Snds[SND_TARGET_FAIL]);
		return;
	}

	targetp = &Objects[Player_ai->target_objnum];

	if ( targetp->type != OBJ_SHIP ){
		return;
	}

	int shipnum = targetp->instance;

	if ( targetp->type == OBJ_SHIP ) {
		if ( Ships[shipnum].flags & TARGET_SHIP_IGNORE_FLAGS ) {
			return;
		}
	}

	for (subsys = GET_FIRST(&Ships[shipnum].subsys_list); subsys != END_OF_LIST(&Ships[shipnum].subsys_list)  ; subsys = GET_NEXT( subsys ) ) {


		if (subsys->flags & SSF_UNTARGETABLE)
			continue;

		get_subsystem_world_pos(targetp, subsys, &subobj_pos);

		vm_vec_normalized_dir(&vec_to_target, &subobj_pos, &Eye_position);
		dot = vm_vec_dot(&Player_obj->orient.vec.fvec, &vec_to_target);

		if ( dot > best_dot ) {
			best_dot = dot;
			if ( best_dot > MIN_DOT_FOR_TARGET )
				nearest_subsys = subsys;
		}

		Assert(best_dot <= 1.0f);
	}

	if ( nearest_subsys != NULL ) {
		set_targeted_subsys(Player_ai, nearest_subsys, Player_ai->target_objnum);
		char r_name[NAME_LENGTH];
		int i;
		strcpy_s(r_name, ship_subsys_get_name(Player_ai->targeted_subsys));
		for (i = 0; r_name[i] > 0; i++) {
			if (r_name[i] == '|')
				r_name[i] = ' ';
		}
		HUD_sourced_printf(HUD_SOURCE_HIDDEN, XSTR( "Targeting subsystem %s.", 323), r_name);
		Ships[shipnum].last_targeted_subobject[Player_num] =  Player_ai->targeted_subsys;
	}
	else {
		snd_play( &Snds[SND_TARGET_FAIL]);
	}
}
