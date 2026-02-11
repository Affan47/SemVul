soldier_duck_down (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_DUCKED)
		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	self->maxs[2] -= 32;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.pausetime = level.time + 1;
	gi.linkentity (self);
}
