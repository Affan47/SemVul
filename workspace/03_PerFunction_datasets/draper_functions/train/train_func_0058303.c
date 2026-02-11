loose_backend__read(git_rawobj *obj, git_odb_backend *backend, const git_oid *oid)
{
	char object_path[GIT_PATH_MAX];

	assert(obj && backend && oid);

	if (locate_object(object_path, (loose_backend *)backend, oid) < 0)
		return GIT_ENOTFOUND;

	return read_loose(obj, object_path);
}
