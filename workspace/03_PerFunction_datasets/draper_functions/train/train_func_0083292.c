profile_ptrace_perm(struct aa_profile *profile,
			       struct aa_profile *peer, u32 request,
			       struct common_audit_data *sa)
{
  struct aa_perms perms = { };


	if (profile_unconfined(profile) ||
	    !PROFILE_MEDIATES(profile, AA_CLASS_PTRACE))
                return 0;

	aad(sa)->peer = &peer->label;
	aa_profile_match_label(profile, &peer->label, AA_CLASS_PTRACE, request,
			       &perms);
	aa_apply_modes_to_perms(profile, &perms);
	return aa_check_perms(profile, &perms, request, sa, audit_ptrace_cb);
}
