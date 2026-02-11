pack_backend__read(
	void **buffer_p, size_t *len_p, git_otype *type_p,
	git_odb_backend *backend, const git_oid *oid)
{
	int error;

	error = pack_backend__read_internal(buffer_p, len_p, type_p, backend, oid);

	if (error != GIT_ENOTFOUND)
		return error;

	if ((error = pack_backend__refresh(backend)) < 0)
		return error;

	return pack_backend__read_internal(buffer_p, len_p, type_p, backend, oid);
}
