git_commit_list_parse(git_revwalk *walk, git_commit_list_node *commit)
{
	git_odb_object *obj;
	int error;

	if (commit->parsed)
		return 0;

	if ((error = git_odb_read(&obj, walk->odb, &commit->oid)) < 0)
		return error;

	if (obj->cached.type != GIT_OBJ_COMMIT) {
		giterr_set(GITERR_INVALID, "Object is no commit object");
		error = -1;
	} else
		error = commit_quick_parse(
			walk, commit,
			(const uint8_t *)git_odb_object_data(obj),
			git_odb_object_size(obj));

	git_odb_object_free(obj);
	return error;
}
