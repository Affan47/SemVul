SP_monster_gladiator (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}


	sound_pain1 = gi.soundindex ("gladiator/pain.wav");
	sound_pain2 = gi.soundindex ("gladiator/gldpain2.wav");
	sound_die = gi.soundindex ("gladiator/glddeth2.wav");
	sound_gun = gi.soundindex ("gladiator/railgun.wav");
	sound_cleaver_swing = gi.soundindex ("gladiator/melee1.wav");
	sound_cleaver_hit = gi.soundindex ("gladiator/melee2.wav");
	sound_cleaver_miss = gi.soundindex ("gladiator/melee3.wav");
	sound_idle = gi.soundindex ("gladiator/gldidle1.wav");
	sound_search = gi.soundindex ("gladiator/gldsrch1.wav");
	sound_sight = gi.soundindex ("gladiator/sight.wav");

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex ("models/monsters/gladiatr/tris.md2");
	VectorSet (self->mins, -32, -32, -24);
	VectorSet (self->maxs, 32, 32, 64);

	self->health = 400;
	self->gib_health = -175;
	self->mass = 400;

	self->pain = gladiator_pain;
	self->die = gladiator_die;

	self->monsterinfo.stand = gladiator_stand;
	self->monsterinfo.walk = gladiator_walk;
	self->monsterinfo.run = gladiator_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.attack = gladiator_attack;
	self->monsterinfo.melee = gladiator_melee;
	self->monsterinfo.sight = gladiator_sight;
	self->monsterinfo.idle = gladiator_idle;
	self->monsterinfo.search = gladiator_search;

	gi.linkentity (self);
	self->monsterinfo.currentmove = &gladiator_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start (self);
}
