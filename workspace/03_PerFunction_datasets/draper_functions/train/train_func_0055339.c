gitrp_reset(git_revpool *pool)
{
	git_commit *commit;
	git_revpool_tableit it;

	git_revpool_tableit_init(pool->commits, &it);

	while ((commit = (git_commit *)git_revpool_tableit_next(&it)) != NULL) {
		commit->seen = 0;
		commit->topo_delay = 0;
		commit->in_degree = 0;
	}

	git_commit_list_clear(&pool->iterator, 0);
	pool->walking = 0;
}
