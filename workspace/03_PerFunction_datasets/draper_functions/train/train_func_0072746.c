expire_reflog(const char *ref, const unsigned char *sha1, int unused, void *cb_data)
{
	struct cmd_reflog_expire_cb *cmd = cb_data;
	struct expire_reflog_cb cb;
	struct ref_lock *lock;
	char *log_file, *newlog_path = NULL;
	int status = 0;

	memset(&cb, 0, sizeof(cb));


	lock = lock_any_ref_for_update(ref, sha1, 0);
	if (!lock)
		return error("cannot lock ref '%s'", ref);
	log_file = xstrdup(git_path("logs/%s", ref));
	if (!file_exists(log_file))
		goto finish;
	if (!cmd->dry_run) {
		newlog_path = xstrdup(git_path("logs/%s.lock", ref));
		cb.newlog = fopen(newlog_path, "w");
	}

	cb.ref_commit = lookup_commit_reference_gently(sha1, 1);
	cb.ref = ref;
	cb.cmd = cmd;
	for_each_reflog_ent(ref, expire_reflog_ent, &cb);
 finish:
	if (cb.newlog) {
		if (fclose(cb.newlog)) {
			status |= error("%s: %s", strerror(errno),
					newlog_path);
			unlink(newlog_path);
		} else if (cmd->updateref &&
			(write_in_full(lock->lock_fd,
				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
			 write_in_full(lock->lock_fd, "\n", 1) != 1 ||
			 close_ref(lock) < 0)) {
			status |= error("Couldn't write %s",
				lock->lk->filename);
			unlink(newlog_path);
		} else if (rename(newlog_path, log_file)) {
			status |= error("cannot rename %s to %s",
					newlog_path, log_file);
			unlink(newlog_path);
		} else if (cmd->updateref && commit_ref(lock)) {
			status |= error("Couldn't set %s", lock->ref_name);
		} else {
			adjust_shared_perm(log_file);
		}
	}
	free(newlog_path);
	free(log_file);
	unlock_ref(lock);
	return status;
}
