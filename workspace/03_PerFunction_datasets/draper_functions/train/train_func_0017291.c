pack_backend__read(void **buffer_p, size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *oid)
{
	struct pack_entry e;
	git_rawobj raw;
	int error;

	if ((error = pack_entry_find(&e, (struct pack_backend *)backend, oid)) < GIT_SUCCESS)
		return error;

	if ((error = packfile_unpack(&raw, (struct pack_backend *)backend, e.p, e.offset)) < GIT_SUCCESS)
		return error;

	*buffer_p = raw.data;
	*len_p = raw.len;
	*type_p = raw.type;

	return GIT_SUCCESS;
}
