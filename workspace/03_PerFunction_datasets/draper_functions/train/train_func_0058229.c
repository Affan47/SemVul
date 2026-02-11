_uid_list_size(uid_t * uid_list_ptr)
{
	int i;

	if (uid_list_ptr == NULL)
		return 0;

	for (i = 0;; i++) {
		if (uid_list_ptr[i] == 0)
			break;
	}

	return i;
}
