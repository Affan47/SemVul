ai_guard_find_nearby_asteroid(object *guarding_objp, object *guarded_objp)
{
	float		dist;

	object	*closest_asteroid_objp=NULL, *danger_asteroid_objp=NULL, *asteroid_objp;
	float		dist_to_self, closest_danger_asteroid_dist=999999.0f, closest_asteroid_dist=999999.0f;

	for ( asteroid_objp = GET_FIRST(&obj_used_list); asteroid_objp != END_OF_LIST(&obj_used_list); asteroid_objp = GET_NEXT(asteroid_objp) ) {
		if ( asteroid_objp->type == OBJ_ASTEROID ) {

			dist = vm_vec_dist_quick(&asteroid_objp->pos, &guarded_objp->pos);
			if ( dist < (MAX_GUARD_DIST + guarded_objp->radius)*2) {
				dist_to_self = vm_vec_dist_quick(&asteroid_objp->pos, &guarding_objp->pos);
				if ( OBJ_INDEX(guarded_objp) == asteroid_collide_objnum(asteroid_objp) ) {
					if( dist_to_self < closest_danger_asteroid_dist ) {
						danger_asteroid_objp=asteroid_objp;
						closest_danger_asteroid_dist=dist_to_self;
					}
				}
				if ( dist_to_self < closest_asteroid_dist ) {

					if ( vm_vec_mag_quick(&asteroid_objp->phys_info.vel) < guarding_objp->phys_info.max_vel.xyz.z ) {
						closest_asteroid_dist = dist_to_self;
						closest_asteroid_objp = asteroid_objp;
					}
				}
			}
		}
	}

	if ( danger_asteroid_objp ) {
		guard_object_was_hit(guarding_objp, danger_asteroid_objp);
	} else if ( closest_asteroid_objp ) {
		guard_object_was_hit(guarding_objp, closest_asteroid_objp);
	}
}
