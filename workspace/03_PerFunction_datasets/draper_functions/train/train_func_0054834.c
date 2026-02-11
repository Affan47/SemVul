nautilus_file_can_set_permissions (NautilusFile *file)
{
	uid_t user_id;

	if (file->details->uid != -1 &&
	    nautilus_file_is_local (file)) {

		user_id = geteuid();


		if (user_id == (uid_t) file->details->uid) {
			return TRUE;
		}


		if (user_id == 0) {
			return TRUE;
		}


		return FALSE;
	}


	return TRUE;
}
