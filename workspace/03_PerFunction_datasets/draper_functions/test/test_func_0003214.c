multi_oo_interp(object *objp)
{

	Assert(Game_mode & GM_MULTIPLAYER);
	if(objp->type != OBJ_SHIP){
		return;
	}
	if((objp->instance < 0) || (objp->instance >= MAX_SHIPS)){
		return;
	}


	oo_arrive_time_next[objp->instance] += flFrametime;


	Assert(objp != Player_obj);
	if(objp != Player_obj){
		ship_fire_primary(objp, 1, 0);
	}


	if((oo_interp_count[objp->instance] < 2) || (oo_arrive_time_count[objp->instance] < 5)){
		return;
	}


	float t = oo_arrive_time_next[objp->instance] / oo_arrive_time_avg_diff[objp->instance];


	if(t > 1.0f){
		physics_sim(&objp->pos, &objp->orient, &objp->phys_info, flFrametime);
		return;
	}


	float u = 0.5f + (t * 0.5f);
	vec3d p_bad, p_good;
	oo_interp_splines[objp->instance][0].bez_get_point(&p_bad, u);
	oo_interp_splines[objp->instance][1].bez_get_point(&p_good, u);
	vm_vec_scale(&p_good, t);
	vm_vec_scale(&p_bad, 1.0f - t);
	vm_vec_add(&objp->pos, &p_bad, &p_good);


	physics_sim_rot(&objp->orient, &objp->phys_info, flFrametime);


}
