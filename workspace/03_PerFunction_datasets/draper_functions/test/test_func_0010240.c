get_reinf_units( void )
{
	List *l = list_create( LIST_NO_AUTO_DELETE, LIST_NO_CALLBACK );
	Unit *u = NULL;

	if (l == NULL) {
		fprintf( stderr, tr("Out of memory\n") );
		return NULL;
	}

	list_reset(reinf);
	while ((u = list_next(reinf)))
		if (u->player == cur_player)
			list_add( l, u );
	return l;
}
