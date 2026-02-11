submodule_release(git_submodule *sm, int decr)
{
	if (!sm)
		return;

	sm->refcount -= decr;

	if (sm->refcount == 0) {
		if (sm->name != sm->path)
			git__free(sm->path);
		git__free(sm->name);
		git__free(sm->url);
		git__free(sm);
	}
}
