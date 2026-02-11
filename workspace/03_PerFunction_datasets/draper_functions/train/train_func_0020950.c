cs_obj_explode(cs_obj_t *o)
{
	o->flags |= CS_OBJ_DYING;


	cs_obj_anim(o, 4, 0, 15, 0, 12);
	if(o->on_dying)
		o->on_dying(o);
}
