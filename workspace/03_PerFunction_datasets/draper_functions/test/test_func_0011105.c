LaserSightThink(edict_t * self)
{
	vec3_t start, end, endp, offset;
	vec3_t forward, right, up, angles;
	trace_t tr;
	int height = 0;


	VectorAdd(self->owner->client->v_angle, self->owner->client->kick_angles, angles);
	AngleVectors(angles, forward, right, up);

	if (self->owner->lasersight != self) {
		self->think = G_FreeEdict;
	}

	if (self->owner->client->pers.firing_style == ACTION_FIRING_CLASSIC)
		height = 8;

	VectorSet(offset, 24, 8, self->owner->viewheight - height);
	P_ProjectSource(self->owner->client, self->owner->s.origin, offset, forward, right, start);
	VectorMA(start, 8192, forward, end);

	PRETRACE();
	tr = gi.trace(start, NULL, NULL, end, self->owner, CONTENTS_SOLID | CONTENTS_MONSTER | CONTENTS_DEADMONSTER);
	POSTTRACE();

	if (tr.fraction != 1) {
		VectorMA(tr.endpos, -4, forward, endp);
		VectorCopy(endp, tr.endpos);
	}

	vectoangles(tr.plane.normal, self->s.angles);
	VectorCopy(tr.endpos, self->s.origin);
	gi.linkentity(self);
	self->nextthink = level.time + 0.1;
}
