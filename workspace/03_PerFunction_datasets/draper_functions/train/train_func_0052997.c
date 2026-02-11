check_patch_list(struct patch *patch)
{
	struct patch *prev_patch = NULL;
	int err = 0;

	for (prev_patch = NULL; patch ; patch = patch->next) {
		if (apply_verbosely)
			say_patch_name(stderr,
				       "Checking patch ", patch, "...\n");
		err |= check_patch(patch, prev_patch);
		prev_patch = patch;
	}
	return err;
}
