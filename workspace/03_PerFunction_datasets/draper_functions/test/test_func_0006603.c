evergreen_surface_check_1d(struct radeon_cs_parser *p,
				      struct eg_surface *surf,
				      const char *prefix)
{
	struct evergreen_cs_track *track = p->track;
	unsigned palign;

	palign = track->group_size / (8 * surf->bpe * surf->nsamples);
	palign = MAX(8, palign);
	surf->layer_size = surf->nbx * surf->nby * surf->bpe;
	surf->base_align = track->group_size;
	surf->palign = palign;
	surf->halign = 8;
	if ((surf->nbx & (palign - 1))) {
		if (prefix) {
			dev_warn(p->dev, "%s:%d %s pitch %d invalid must be aligned with %d (%d %d %d)\n",
				 __func__, __LINE__, prefix, surf->nbx, palign,
				 track->group_size, surf->bpe, surf->nsamples);
		}
		return -EINVAL;
	}
	if ((surf->nby & (8 - 1))) {
		if (prefix) {
			dev_warn(p->dev, "%s:%d %s height %d invalid must be aligned with 8\n",
				 __func__, __LINE__, prefix, surf->nby);
		}
		return -EINVAL;
	}
	return 0;
}
