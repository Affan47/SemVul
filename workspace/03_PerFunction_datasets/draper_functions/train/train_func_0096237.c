lock_ref_sha1_basic(const char *ref, const unsigned char *old_sha1, int flags, int *type_p)
{
	char *ref_file;
	const char *orig_ref = ref;
	struct ref_lock *lock;
	struct stat st;
	int last_errno = 0;
	int type;
	int mustexist = (old_sha1 && !is_null_sha1(old_sha1));

	lock = xcalloc(1, sizeof(struct ref_lock));
	lock->lock_fd = -1;

	ref = resolve_ref(ref, lock->old_sha1, mustexist, &type);
	if (!ref && errno == EISDIR) {


		ref_file = git_path("%s", orig_ref);
		if (remove_empty_directories(ref_file)) {
			last_errno = errno;
			error("there are still refs under '%s'", orig_ref);
			goto error_return;
		}
		ref = resolve_ref(orig_ref, lock->old_sha1, mustexist, &type);
	}
	if (type_p)
	    *type_p = type;
	if (!ref) {
		last_errno = errno;
		error("unable to resolve reference %s: %s",
			orig_ref, strerror(errno));
		goto error_return;
	}


	if (is_null_sha1(lock->old_sha1) &&
            !is_refname_available(ref, NULL, get_packed_refs(), 0))
		goto error_return;

	lock->lk = xcalloc(1, sizeof(struct lock_file));

	if (flags & REF_NODEREF)
		ref = orig_ref;
	lock->ref_name = xstrdup(ref);
	lock->orig_ref_name = xstrdup(orig_ref);
	ref_file = git_path("%s", ref);
	if (lstat(ref_file, &st) && errno == ENOENT)
		lock->force_write = 1;
	if ((flags & REF_NODEREF) && (type & REF_ISSYMREF))
		lock->force_write = 1;

	if (safe_create_leading_directories(ref_file)) {
		last_errno = errno;
		error("unable to create directory for %s", ref_file);
		goto error_return;
	}
	lock->lock_fd = hold_lock_file_for_update(lock->lk, ref_file, 1);

	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;

 error_return:
	unlock_ref(lock);
	errno = last_errno;
	return NULL;
}
