label_components_match(struct aa_profile *profile,
				  struct aa_label *label, bool stack,
				  unsigned int start, bool subns, u32 request,
				  struct aa_perms *perms)
{
	struct aa_profile *tp;
	struct label_it i;
	struct aa_perms tmp;
	struct path_cond cond = { };
	unsigned int state = 0;


	label_for_each(i, label, tp) {
		if (!aa_ns_visible(profile->ns, tp->ns, subns))
			continue;
		state = match_component(profile, tp, stack, start);
		if (!state)
			goto fail;
		goto next;
	}


	return 0;

next:
	tmp = aa_compute_fperms(profile->file.dfa, state, &cond);
	aa_apply_modes_to_perms(profile, &tmp);
	aa_perms_accum(perms, &tmp);
	label_for_each_cont(i, label, tp) {
		if (!aa_ns_visible(profile->ns, tp->ns, subns))
			continue;
		state = match_component(profile, tp, stack, start);
		if (!state)
			goto fail;
		tmp = aa_compute_fperms(profile->file.dfa, state, &cond);
		aa_apply_modes_to_perms(profile, &tmp);
		aa_perms_accum(perms, &tmp);
	}

	if ((perms->allow & request) != request)
		return -EACCES;

	return 0;

fail:
	*perms = nullperms;
	return -EACCES;
}
