shadow_step(struct shadow_spine *s, dm_block_t b,
		struct dm_btree_value_type *vt)
{
	int r;

	if (s->count == 2) {
		unlock_block(s->info, s->nodes[0]);
		s->nodes[0] = s->nodes[1];
		s->count--;
	}

	r = bn_shadow(s->info, b, vt, s->nodes + s->count);
	if (!r) {
		if (!s->count)
			s->root = dm_block_location(s->nodes[0]);

		s->count++;
	}

	return r;
}
