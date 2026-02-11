uset_affine_hull_bounded(struct isl_basic_set *bset)
{
	struct isl_vec *sample = NULL;
	struct isl_basic_set *hull;
	struct isl_tab *tab = NULL;
	unsigned dim;

	if (isl_basic_set_plain_is_empty(bset))
		return bset;

	dim = isl_basic_set_n_dim(bset);

	if (bset->sample && bset->sample->size == 1 + dim) {
		int contains = isl_basic_set_contains(bset, bset->sample);
		if (contains < 0)
			goto error;
		if (contains) {
			if (dim == 0)
				return bset;
			sample = isl_vec_copy(bset->sample);
		} else {
			isl_vec_free(bset->sample);
			bset->sample = NULL;
		}
	}

	tab = isl_tab_from_basic_set(bset, 1);
	if (!tab)
		goto error;
	if (tab->empty) {
		isl_tab_free(tab);
		isl_vec_free(sample);
		return isl_basic_set_set_to_empty(bset);
	}

	if (!sample) {
		struct isl_tab_undo *snap;
		snap = isl_tab_snap(tab);
		sample = isl_tab_sample(tab);
		if (isl_tab_rollback(tab, snap) < 0)
			goto error;
		isl_vec_free(tab->bmap->sample);
		tab->bmap->sample = isl_vec_copy(sample);
	}

	if (!sample)
		goto error;
	if (sample->size == 0) {
		isl_tab_free(tab);
		isl_vec_free(sample);
		return isl_basic_set_set_to_empty(bset);
	}

	hull = initialize_hull(bset, sample);

	hull = extend_affine_hull(tab, hull, bset);
	isl_basic_set_free(bset);
	isl_tab_free(tab);

	return hull;
error:
	isl_vec_free(sample);
	isl_tab_free(tab);
	isl_basic_set_free(bset);
	return NULL;
}
