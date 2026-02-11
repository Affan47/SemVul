auth_pipe_enumerate(void(*cb_func)(const char *name,
	                                      uid_t uid,
	                                      gid_t gid,
	                                const char *homedir,
	                                const char *maildir,
					const char *options,
	                                      void *void_arg),
	                         void *void_arg)
{
	int rdfd, wrfd, rc;

	if (disabled_flag)
		return;

	if (getPipe(&rdfd, &wrfd))
		return;
	rc = _auth_enumerate(wrfd, rdfd, cb_func, void_arg);
	if (rc > 0) closePipe();
}
