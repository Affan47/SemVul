beam_ok_to_fire(beam *b)
{

	if (b->objp->signature != b->sig) {
		mprintf(("BEAM : killing beam because of invalid parent object SIGNATURE!\n"));
		return -1;
	}


	if (b->objp->type != OBJ_SHIP) {
		mprintf(("BEAM : killing beam because of invalid parent object TYPE!\n"));
		return -1;
	}


	if (b->type == BEAM_TYPE_C) {
		ship *shipp = &Ships[b->objp->instance];

		if (shipp->weapon_energy <= 0.0f) {


			if ( OBJ_INDEX(Player_obj) == shipp->objnum && !(b->life_left>0.0f)) {
				extern int ship_maybe_play_primary_fail_sound();
				ship_maybe_play_primary_fail_sound();
			}


			return 0;
		} else {
			return 1;
		}
	}

	if (!(b->flags & BF_FORCE_FIRING)) {

		if (b->subsys->current_hits <= 0.0f) {
			mprintf(("BEAM : killing beam because turret has been destroyed!\n"));
			return -1;
		}


		if (ship_subsys_disrupted(b->subsys)) {
			return -1;
		}


		vec3d aim_dir;
		vm_vec_sub(&aim_dir, &b->last_shot, &b->last_start);
		vm_vec_normalize(&aim_dir);

		if (The_mission.ai_profile->flags & AIPF_FORCE_BEAM_TURRET_FOV) {
			vec3d turret_normal;

			if (b->flags & BF_IS_FIGHTER_BEAM) {
				turret_normal = b->objp->orient.vec.fvec;
				b->subsys->system_info->flags &= ~MSS_FLAG_TURRET_ALT_MATH;
			} else {
				vm_vec_unrotate(&turret_normal, &b->subsys->system_info->turret_norm, &b->objp->orient);
			}

			if (!(turret_fov_test(b->subsys, &turret_normal, &aim_dir))) {
				nprintf(("BEAM", "BEAM : powering beam down because of FOV condition!\n"));
				return 0;
			}
		} else {
			vec3d turret_dir, turret_pos, temp;
			beam_get_global_turret_gun_info(b->objp, b->subsys, &turret_pos, &turret_dir, 1, &temp, (b->flags & BF_IS_FIGHTER_BEAM) > 0);
			if (vm_vec_dotprod(&aim_dir, &turret_dir) < b->subsys->system_info->turret_fov) {
				nprintf(("BEAM", "BEAM : powering beam down because of FOV condition!\n"));
				return 0;
			}
		}
	}


	return 1;
}
