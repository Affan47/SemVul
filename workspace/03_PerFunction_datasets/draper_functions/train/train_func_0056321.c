SP_target_actor (edict_t *self)
{
	if (!self->targetname)
		gi.dprintf ("%s with no targetname at %s\n", self->classname, vtos(self->s.origin));

	self->solid = SOLID_TRIGGER;
	self->touch = target_actor_touch;
	VectorSet (self->mins, -8, -8, -8);
	VectorSet (self->maxs, 8, 8, 8);
	self->svflags = SVF_NOCLIENT;

	if (self->spawnflags & 1)
	{
		if (!self->speed)
			self->speed = 200;
		if (!st.height)
			st.height = 200;
		if (self->s.angles[YAW] == 0)
			self->s.angles[YAW] = 360;
		G_SetMovedir (self->s.angles, self->movedir);
		self->movedir[2] = st.height;
	}

	gi.linkentity (self);
}
