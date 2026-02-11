drawable_reset_bounds(Drawable *dr, GF_VisualManager *visual)
{
	DRInfo *dri;
	BoundInfo *bi, *_cur;

	dri = dr->dri;
	while (dri) {
		if (dri->visual != visual) {
			dri = dri->next;
			continue;
		}

		bi = dri->previous_bounds;
		while (bi) {
			_cur = bi;
			bi = bi->next;
			gf_free(_cur);
		}
		dri->previous_bounds = NULL;
		return;
	}
}
