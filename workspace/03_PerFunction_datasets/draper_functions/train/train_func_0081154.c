dtrs_match_callback(void* extra, int image_ind, int ref_ind, double dist2) {
	tweak_t* t = extra;
	image_ind = kdtree_permute(t->kd_image, image_ind);
	ref_ind   = kdtree_permute(t->kd_ref,   ref_ind);
	il_append(t->image, image_ind);
	il_append(t->ref, ref_ind);
	dl_append(t->dist2, dist2);
	if (t->weight)
		dl_append(t->weight, exp(-dist2 / (2.0 * t->jitterd2)));
}
