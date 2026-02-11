netbench_algo_matrix_run_master(struct linked_list *results, int tasknb)
{
	int i, j;

	i = tasknb;

	while (i--)
	{
		if (i == NETBENCH_MASTER_RANK)
			continue;
		j = tasknb;

		while (j--)
		{
			if (j == NETBENCH_MASTER_RANK)
				continue;

			if (j == i)
			{
				netbench_comm_role_send(NETBENCH_ROLE_TESTER,j);
			}

			else
			{
				netbench_comm_role_send(NETBENCH_ROLE_TESTED,j);
				netbench_comm_rank_send(i,j);
			}
		}
		netbench_list_result_recv(results,i);
	}
}
