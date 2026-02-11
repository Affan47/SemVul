cleanup_chmod_root(void *ref)
{
	mode_t *mode = ref;

	if (*mode != 0) {
		(void)p_umask(*mode);
		git__free(mode);
	}

	git_futils_rmdir_r("r", NULL, GIT_RMDIR_EMPTY_HIERARCHY);
}
