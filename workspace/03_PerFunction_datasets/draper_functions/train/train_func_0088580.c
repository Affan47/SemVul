loose_parse_symbolic(git_reference *ref, git_fbuffer *file_content)
{
	const unsigned int header_len = strlen(GIT_SYMREF);
	const char *refname_start;
	char *eol;
	reference_symbolic *ref_sym;

	refname_start = (const char *)file_content->data;
	ref_sym = (reference_symbolic *)ref;

	if (file_content->len < (header_len + 1))
		return git__throw(GIT_EOBJCORRUPTED,
			"Failed to parse loose reference. Object too short");


	refname_start += header_len;

	free(ref_sym->target);
	ref_sym->target = git__strdup(refname_start);
	if (ref_sym->target == NULL)
		return GIT_ENOMEM;


	eol = strchr(ref_sym->target, '\n');
	if (eol == NULL)
		return git__throw(GIT_EOBJCORRUPTED,
			"Failed to parse loose reference. Missing EOL");

	*eol = '\0';
	if (eol[-1] == '\r')
		eol[-1] = '\0';

	return GIT_SUCCESS;
}
