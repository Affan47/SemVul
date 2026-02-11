flyer_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	end;
	vec3_t	dir;
	int		effect;

	if ((self->s.frame == FRAME_attak204) || (self->s.frame == FRAME_attak207) || (self->s.frame == FRAME_attak210))
		effect = EF_HYPERBLASTER;
	else
		effect = 0;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);

	VectorCopy (self->enemy->s.origin, end);
	end[2] += self->enemy->viewheight;
	VectorSubtract (end, start, dir);

	monster_fire_blaster (self, start, dir, 1, 1000, flash_number, effect);
}
