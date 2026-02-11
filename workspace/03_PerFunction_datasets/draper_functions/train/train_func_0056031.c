enqueue_tag(git_object **out, git_push *push, git_oid *id)
{
	git_object *obj = NULL, *target = NULL;
	int error;

	if ((error = git_object_lookup(&obj, push->repo, id, GIT_OBJ_TAG)) < 0)
		return error;

	while (git_object_type(obj) == GIT_OBJ_TAG) {
		if ((error = git_packbuilder_insert(push->pb, git_object_id(obj), NULL)) < 0)
			break;

		if ((error = git_tag_target(&target, (git_tag *) obj)) < 0)
			break;

		git_object_free(obj);
		obj = target;
	}

	if (error < 0)
		git_object_free(obj);
	else
		*out = obj;

	return error;
}
