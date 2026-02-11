git_reference_set_target(git_reference *ref, const char *target)
{
	char normalized[GIT_REFNAME_MAX];

	if ((ref->flags & GIT_REF_SYMBOLIC) == 0) {
		giterr_set(GITERR_REFERENCE,
			"Cannot set symbolic target on a direct reference");
		return -1;
	}

	if (normalize_name(normalized, sizeof(normalized), target, 0))
		return -1;

	git__free(ref->target.symbolic);
	ref->target.symbolic = git__strdup(normalized);
	GITERR_CHECK_ALLOC(ref->target.symbolic);

	return loose_write(ref);
}
