FL_make (edict_t * self)
{
	vec3_t start, forward, right, end;

	if (!darkmatch->value)
		return;

	if ((self->deadflag == DEAD_DEAD) || (self->solid == SOLID_NOT))
	{
		if (self->flashlight)
		{
			G_FreeEdict (self->flashlight);
			self->flashlight = NULL;
		}
		return;
	}

	gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/flashlight.wav"), 1,
	ATTN_NORM, 0);

	if (self->flashlight)
	{
		G_FreeEdict (self->flashlight);
		self->flashlight = NULL;
		return;
	}

	AngleVectors (self->client->v_angle, forward, right, NULL);

	VectorSet (end, 100, 0, 0);
	G_ProjectSource (self->s.origin, end, forward, right, start);

	self->flashlight = G_Spawn ();
	self->flashlight->owner = self;
	self->flashlight->movetype = MOVETYPE_NOCLIP;
	self->flashlight->solid = SOLID_NOT;
	self->flashlight->classname = "flashlight";
	self->flashlight->s.modelindex = gi.modelindex ("sprites/null.sp2");
	self->flashlight->s.skinnum = 0;
	self->flashlight->s.effects |= EF_HYPERBLASTER;
	self->flashlight->think = FL_think;
	self->flashlight->nextthink = level.time + 0.1;
}
