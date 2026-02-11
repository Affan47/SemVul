fireball_is_warp(object * obj)
{
	int			num, objnum;
	fireball		*fb;

	num = obj->instance;
	objnum = OBJ_INDEX(obj);
	Assert( Fireballs[num].objnum == objnum );

	fb = &Fireballs[num];

	if ( fb->fireball_render_type == FIREBALL_WARP_EFFECT)
		return 1;

	return 0;
}
