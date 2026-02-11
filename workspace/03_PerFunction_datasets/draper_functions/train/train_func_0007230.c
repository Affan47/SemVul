git_odb_foreach(git_odb *db, int (*cb)(git_oid *oid, void *data), void *data)
{
	unsigned int i;
	backend_internal *internal;

	git_vector_foreach(&db->backends, i, internal) {
		git_odb_backend *b = internal->backend;
		int error = b->foreach(b, cb, data);
		if (error < 0)
			return error;
	}

	return 0;
}
