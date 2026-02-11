_wi_fs_delete_file(wi_string_t *path, wi_fs_delete_path_callback_t *callback) {
	if(unlink(wi_string_cstring(path)) < 0) {
		wi_error_set_errno(errno);

		return false;
	} else {
		if(callback)
			(*callback)(path);

		return true;
	}
}
