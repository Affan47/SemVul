local_negotiate_fetch(
	git_transport *transport,
	git_repository *repo,
	const git_remote_head * const *refs,
	size_t count)
{
	transport_local *t = (transport_local*)transport;
	git_remote_head *rhead;
	unsigned int i;

	GIT_UNUSED(refs);
	GIT_UNUSED(count);


	git_vector_foreach(&t->refs, i, rhead) {
		git_object *obj;

		int error = git_revparse_single(&obj, repo, rhead->name);
		if (!error)
			git_oid_cpy(&rhead->loid, git_object_id(obj));
		else if (error != GIT_ENOTFOUND)
			return error;
		else
			giterr_clear();
		git_object_free(obj);
	}

	return 0;
}
