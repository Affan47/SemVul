lock_path (const gchar *path,
           guint32 *lockid)
{
	struct _lock_info *info = NULL;
	gint res = CAMEL_LOCK_HELPER_STATUS_OK;
	struct stat st;

	d (fprintf (stderr, "locking path '%s' id = %d\n", path, lock_id));


	info = lock_info_list;
	while (info) {
		if (!strcmp (info->path, path)) {
			info->depth++;
			return CAMEL_LOCK_HELPER_STATUS_OK;
		}
		info = info->next;
	}


	if (g_stat (path, &st) == -1
	    || st.st_uid != getuid ()
	    || !S_ISREG (st.st_mode)
	    || (st.st_mode & 0400) == 0) {
		return CAMEL_LOCK_HELPER_STATUS_INVALID;
	}

	info = malloc (sizeof (*info) + strlen (path));
	if (info == NULL) {
		res = CAMEL_LOCK_HELPER_STATUS_NOMEM;
		goto fail;
	}


	if (camel_lock_dot (path, NULL) == -1) {
#ifdef SETEUID_SAVES
		if (lock_real_uid != lock_root_uid) {
			if (seteuid (lock_root_uid) != -1) {
				if (camel_lock_dot (path, NULL) == -1) {
					seteuid (lock_real_uid);
					res = CAMEL_LOCK_HELPER_STATUS_SYSTEM;
					goto fail;
				}
				seteuid (lock_real_uid);
			} else {
				res = CAMEL_LOCK_HELPER_STATUS_SYSTEM;
				goto fail;
			}
		} else {
			res = CAMEL_LOCK_HELPER_STATUS_SYSTEM;
			goto fail;
		}
#else
		res = CAMEL_LOCK_HELPER_STATUS_SYSTEM;
		goto fail;
#endif
	} else {
		info->uid = lock_real_uid;
	}

	g_strlcpy (info->path, path, strlen (path) + 1);
	info->id = lock_id;
	info->depth = 1;
	info->next = lock_info_list;
	info->stamp = time (NULL);
	lock_info_list = info;

	if (lockid)
		*lockid = lock_id;

	lock_id++;

	d (fprintf (stderr, "lock ok\n"));

	return res;
fail:
	d (fprintf (stderr, "lock failed\n"));

	if (info)
		free (info);

	return res;
}
