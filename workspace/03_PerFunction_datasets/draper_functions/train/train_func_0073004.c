boss2_attack (edict_t *self)
{
	vec3_t	vec;
	float	range;

	VectorSubtract (self->enemy->s.origin, self->s.origin, vec);
	range = VectorLength (vec);

	if (range <= 125)
	{
		self->monsterinfo.currentmove = &boss2_move_attack_pre_mg;
	}
	else
	{
		if (random() <= 0.6)
			self->monsterinfo.currentmove = &boss2_move_attack_pre_mg;
		else
			self->monsterinfo.currentmove = &boss2_move_attack_rocket;
	}
}
