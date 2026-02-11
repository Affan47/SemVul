diff_patch_with_delta_alloc(
	diff_patch_with_delta **out,
	const char **old_path,
	const char **new_path)
{
	diff_patch_with_delta *pd;
	size_t old_len = *old_path ? strlen(*old_path) : 0;
	size_t new_len = *new_path ? strlen(*new_path) : 0;

	*out = pd = git__calloc(1, sizeof(*pd) + old_len + new_len + 2);
	GITERR_CHECK_ALLOC(pd);

	pd->patch.flags = GIT_DIFF_PATCH_ALLOCATED;

	if (*old_path) {
		memcpy(&pd->paths[0], *old_path, old_len);
		*old_path = &pd->paths[0];
	} else if (*new_path)
		*old_path = &pd->paths[old_len + 1];

	if (*new_path) {
		memcpy(&pd->paths[old_len + 1], *new_path, new_len);
		*new_path = &pd->paths[old_len + 1];
	} else if (*old_path)
		*new_path = &pd->paths[0];

	return 0;
}
