sprites_differ (struct draw_info *dip, struct draw_info *dip_old)
{
	struct sprite_entry *this_first = curr_sprite_entries + dip->first_sprite_entry;
	struct sprite_entry *this_last = curr_sprite_entries + dip->last_sprite_entry;
	struct sprite_entry *prev_first = prev_sprite_entries + dip_old->first_sprite_entry;
	int npixels;
	int i;

	if (dip->nr_sprites != dip_old->nr_sprites)
		return 1;

	if (dip->nr_sprites == 0)
		return 0;

	for (i = 0; i < dip->nr_sprites; i++) {
		if (this_first[i].pos != prev_first[i].pos
			|| this_first[i].max != prev_first[i].max
			|| this_first[i].has_attached != prev_first[i].has_attached)
			return 1;
	}

    npixels = this_last->first_pixel + (this_last->max - this_last->pos) - this_first->first_pixel;
	if (memcmp (spixels + this_first->first_pixel, spixels + prev_first->first_pixel,
		npixels * sizeof (uae_u16)) != 0)
		return 1;
	if (memcmp (spixstate.bytes + this_first->first_pixel, spixstate.bytes + prev_first->first_pixel, npixels) != 0)
		return 1;
	return 0;
}
