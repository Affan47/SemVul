setup_reference(const char *repo)
{
	const char *ref_git;
	char *ref_git_copy;

	struct remote *remote;
	struct transport *transport;
	const struct ref *extra;

	ref_git = real_path(option_reference);

	if (is_directory(mkpath("%s/.git/objects", ref_git)))
		ref_git = mkpath("%s/.git", ref_git);
	else if (!is_directory(mkpath("%s/objects", ref_git)))
		die(_("reference repository '%s' is not a local directory."),
		    option_reference);

	ref_git_copy = xstrdup(ref_git);

	add_to_alternates_file(ref_git_copy);

	remote = remote_get(ref_git_copy);
	transport = transport_get(remote, ref_git_copy);
	for (extra = transport_get_remote_refs(transport); extra;
	     extra = extra->next)
		add_extra_ref(extra->name, extra->old_sha1, 0);

	transport_disconnect(transport);

	free(ref_git_copy);
}
