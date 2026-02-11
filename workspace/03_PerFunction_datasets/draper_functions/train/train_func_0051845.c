profile_umount(struct aa_profile *profile, struct path *path,
			  char *buffer)
{
	struct aa_perms perms = { };
	const char *name = NULL, *info = NULL;
	unsigned int state;
	int error;

	AA_BUG(!profile);
	AA_BUG(!path);

	error = aa_path_name(path, path_flags(profile, path), buffer, &name,
			     &info, profile->disconnected);
	if (error)
		goto audit;

	state = aa_dfa_match(profile->policy.dfa,
			     profile->policy.start[AA_CLASS_MOUNT],
			     name);
	perms = compute_mnt_perms(profile->policy.dfa, state);
	if (AA_MAY_UMOUNT & ~perms.allow)
		error = -EACCES;

audit:
	return audit_mount(profile, OP_UMOUNT, name, NULL, NULL, NULL, 0, NULL,
			   AA_MAY_UMOUNT, &perms, info, error);
}
