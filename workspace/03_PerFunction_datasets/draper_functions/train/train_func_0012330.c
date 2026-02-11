fireball_delete_all()
{
	fireball	*fb;
	int		i;

	for ( i = 0; i < MAX_FIREBALLS; i++ ) {
		fb = &Fireballs[i];
		if ( fb->objnum != -1 ) {
			obj_delete(fb->objnum);
		}
	}
}
