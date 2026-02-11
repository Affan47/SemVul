walk_and_search(git_object **out, git_revwalk *walk, regex_t *regex)
{
	int error;
	git_oid oid;
	git_object *obj;

	while (!(error = git_revwalk_next(&oid, walk))) {

		if ((error = git_object_lookup(&obj, git_revwalk_repository(walk), &oid, GIT_OBJ_COMMIT) < 0) &&
			(error != GIT_ENOTFOUND))
			return -1;

		if (!regexec(regex, git_commit_message((git_commit*)obj), 0, NULL, 0)) {
			*out = obj;
			return 0;
		}

		git_object_free(obj);
	}

	if (error < 0 && error == GIT_ITEROVER)
		error = GIT_ENOTFOUND;

	return error;
}
