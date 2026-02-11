git_reference_set_target(git_reference *ref, const char *target)
{
	reference_symbolic *ref_sym;

	if ((ref->type & GIT_REF_SYMBOLIC) == 0)
		return git__throw(GIT_EINVALIDREFSTATE, "Failed to set reference target. Not a symbolic reference");

	ref_sym = (reference_symbolic *)ref;

	free(ref_sym->target);
	ref_sym->target = git__strdup(target);
	if (ref_sym->target == NULL)
		return GIT_ENOMEM;

	return loose_write(ref);
}
