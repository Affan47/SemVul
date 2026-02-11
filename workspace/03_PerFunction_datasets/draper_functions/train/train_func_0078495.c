_post_user_list(List user_list)
{
	slurmdb_user_rec_t *user = NULL;
	ListIterator itr = list_iterator_create(user_list);

	while ((user = list_next(itr))) {
		uid_t pw_uid;


		if (!user->default_wckey)
			user->default_wckey = xstrdup("");
		if (uid_from_string (user->name, &pw_uid) < 0) {
			if (slurmdbd_conf)
				debug("post user: couldn't get a "
				      "uid for user %s",
				      user->name);
			user->uid = NO_VAL;
		} else
			user->uid = pw_uid;
	}
	list_iterator_destroy(itr);
	return SLURM_SUCCESS;
}
