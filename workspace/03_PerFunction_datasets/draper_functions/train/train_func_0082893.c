obj_collide_retime_cached_pairs(int checkdly)
{
	SCP_hash_map<uint, collider_pair>::iterator it;

	for ( it = Collision_cached_pairs.begin(); it != Collision_cached_pairs.end(); ++it ) {
		it->second.next_check_time = timestamp(checkdly);
	}
}
