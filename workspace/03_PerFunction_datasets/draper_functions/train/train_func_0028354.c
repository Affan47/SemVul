dereference_object(git_object **dereferenced, git_object *obj)
{
	git_otype type = git_object_type(obj);

	switch (type) {
	case GIT_OBJ_COMMIT:
		return git_commit_tree((git_tree **)dereferenced, (git_commit*)obj);

	case GIT_OBJ_TAG:
		return git_tag_target(dereferenced, (git_tag*)obj);

	case GIT_OBJ_BLOB:
		return GIT_ENOTFOUND;

	case GIT_OBJ_TREE:
		return GIT_EAMBIGUOUS;

	default:
		return GIT_EINVALIDSPEC;
	}
}
