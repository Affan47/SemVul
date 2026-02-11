insane_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	if (self->health <= self->gib_health)
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_IDLE, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	gi.sound (self, CHAN_VOICE, gi.soundindex(va("player/male/death%i.wav", (rand()%4)+1)), 1, ATTN_IDLE, 0);

	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;

	if (self->spawnflags & 8)
	{
		insane_dead (self);
	}
	else
	{
		if ( ((self->s.frame >= FRAME_crawl1) && (self->s.frame <= FRAME_crawl9)) || ((self->s.frame >= FRAME_stand99) && (self->s.frame <= FRAME_stand160)) )
			self->monsterinfo.currentmove = &insane_move_crawl_death;
		else
			self->monsterinfo.currentmove = &insane_move_stand_death;
	}
}
