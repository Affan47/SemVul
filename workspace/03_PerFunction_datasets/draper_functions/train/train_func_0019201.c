locate_object_short_oid(char *object_location, git_oid *res_oid, loose_backend *backend, const git_oid *short_oid, unsigned int len)
{
	char *objects_dir = backend->objects_dir;
	size_t dir_len = strlen(objects_dir);
	loose_locate_object_state state;
	int error;

	if (dir_len+43 > GIT_PATH_MAX)
		return git__throw(GIT_ERROR, "Failed to locate object from short oid. Object path too long");

	strcpy(object_location, objects_dir);


	if (object_location[dir_len-1] != '/')
		object_location[dir_len++] = '/';


	git_oid_fmt((char *)state.short_oid, short_oid);

	sprintf(object_location+dir_len, "%.2s/", state.short_oid);


	if (git_futils_exists(object_location) || git_futils_isdir(object_location))
		return git__throw(GIT_ENOTFOUND, "Failed to locate object from short oid. Object not found");

	state.dir_len = dir_len+3;
	state.short_oid_len = len;
	state.found = 0;

	error = git_futils_direach(object_location, GIT_PATH_MAX, fn_locate_object_short_oid, &state);
	if (error) {
		return git__rethrow(error, "Failed to locate object from short oid");
	}
	if (!state.found) {
		return git__throw(GIT_ENOTFOUND, "Failed to locate object from short oid. Object not found");
	}


	error = git_oid_fromstr(res_oid, (char *)state.res_oid);
	if (error) {
		return git__rethrow(error, "Failed to locate object from short oid");
	}


	git_oid_pathfmt(object_location+dir_len, res_oid);

	return GIT_SUCCESS;
}
