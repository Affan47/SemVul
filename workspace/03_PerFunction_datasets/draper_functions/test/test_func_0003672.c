ai_guard_find_nearby_object()
{
	ship			*shipp = &Ships[Pl_objp->instance];
	ai_info		*aip = &Ai_info[shipp->ai_index];
	object		*guardobjp;
	int			bomb_found=0;

	guardobjp = &Objects[aip->guard_objnum];


	bomb_found = ai_guard_find_nearby_bomb(Pl_objp, guardobjp);

	if ( !bomb_found ) {

		ai_guard_find_nearby_ship(Pl_objp, guardobjp);


		if ( (aip->target_objnum == -1) && asteroid_count() ) {
			ai_guard_find_nearby_asteroid(Pl_objp, guardobjp);
		}
	}
}
