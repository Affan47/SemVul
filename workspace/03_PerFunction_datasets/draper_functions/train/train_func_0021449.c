git_odb_foreach(git_odb *db, git_odb_foreach_cb cb, void *payload)
{
	unsigned int i;
	backend_internal *internal;

	git_vector_foreach(&db->backends, i, internal) {
		git_odb_backend *b = internal->backend;
		int error = b->foreach(b, cb, payload);
		if (error < 0)
			return error;
	}

	return 0;
}
