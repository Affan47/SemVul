verify_node_list(char **node_list_pptr, enum task_dist_states dist,
		      int task_count)
{
	char *nodelist = NULL;

	xassert (node_list_pptr);
	xassert (*node_list_pptr);

	if (strchr(*node_list_pptr, '/') == NULL)
		return true;


	if (dist == SLURM_DIST_ARBITRARY)
		nodelist = slurm_read_hostfile(*node_list_pptr, task_count);
	else
		nodelist = slurm_read_hostfile(*node_list_pptr, NO_VAL);

	if (!nodelist)
		return false;

	xfree(*node_list_pptr);
	*node_list_pptr = xstrdup(nodelist);
	free(nodelist);

	return true;
}
