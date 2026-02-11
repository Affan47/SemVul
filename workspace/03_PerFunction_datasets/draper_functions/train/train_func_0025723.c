git__shutdown(void)
{
	int pos;

	for (pos = git_atomic_get(&git__n_shutdown_callbacks); pos > 0; pos = git_atomic_dec(&git__n_shutdown_callbacks)) {
		git_global_shutdown_fn cb = git__swap(git__shutdown_callbacks[pos - 1], NULL);
		if (cb != NULL)
			cb();
	}

}
