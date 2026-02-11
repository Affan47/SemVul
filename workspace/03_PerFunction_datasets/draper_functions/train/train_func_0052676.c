label_compound_match(struct aa_profile *profile,
				struct aa_label *label,
				unsigned int state, bool subns, u32 request,
				struct aa_perms *perms)
{
	struct aa_profile *tp;
	struct label_it i;


	label_for_each(i, label, tp) {
		if (!aa_ns_visible(profile->ns, tp->ns, subns))
			continue;
		state = match_component(profile, tp, state);
		if (!state)
			goto fail;
		goto next;
	}


	*perms = allperms;
	return 0;

next:
	label_for_each_cont(i, label, tp) {
		if (!aa_ns_visible(profile->ns, tp->ns, subns))
			continue;
		state = aa_dfa_match(profile->policy.dfa, state, "//&");
		state = match_component(profile, tp, state);
		if (!state)
			goto fail;
	}
	aa_compute_perms(profile->policy.dfa, state, perms);
	aa_apply_modes_to_perms(profile, perms);
	if ((perms->allow & request) != request)
		return -EACCES;

	return 0;

fail:
	*perms = nullperms;
	return state;
}
