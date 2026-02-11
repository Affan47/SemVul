beam_get_global_turret_gun_info(object *objp, ship_subsys *ssp, vec3d *gpos, vec3d *gvec, int use_angles, vec3d *targetp, bool fighter_beam){
		ship_get_global_turret_gun_info(objp, ssp, gpos, gvec, use_angles, targetp);
	if(fighter_beam)*gvec = objp->orient.vec.fvec;
}
