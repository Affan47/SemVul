brain_hit_left (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, self->mins[0], 8);
	if (fire_hit (self, aim, (15 + (rand() %5)), 40))
		gi.sound (self, CHAN_WEAPON, sound_melee3, 1, ATTN_NORM, 0);
}
