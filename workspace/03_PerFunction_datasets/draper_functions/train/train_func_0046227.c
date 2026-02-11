git_odb_read_header(size_t *len_p, git_otype *type_p, git_odb *db, const git_oid *id)
{
	int error;
	git_odb_object *object;

	error = git_odb__read_header_or_object(&object, len_p, type_p, db, id);

	if (object)
		git_odb_object_free(object);

	return error;
}
