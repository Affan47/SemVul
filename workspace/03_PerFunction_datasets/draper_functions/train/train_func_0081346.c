loose_parse_symbolic(git_reference *ref, git_buf *file_content)
{
	const unsigned int header_len = (unsigned int)strlen(GIT_SYMREF);
	const char *refname_start;

	refname_start = (const char *)file_content->ptr;

	if (git_buf_len(file_content) < header_len + 1) {
		giterr_set(GITERR_REFERENCE, "Corrupted loose reference file");
		return -1;
	}


	refname_start += header_len;

	ref->target.symbolic = git__strdup(refname_start);
	GITERR_CHECK_ALLOC(ref->target.symbolic);

	return 0;
}
