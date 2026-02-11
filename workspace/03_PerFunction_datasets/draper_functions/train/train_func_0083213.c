t_tasks13(void) {
	int	result;

	T13_nfails = 0;
	T13_nprobs = 0;


	t_info("testing purge on 2,4,8 expecting 1\n");
	t_taskpurge_x(1, 4, 7, &senders[2], 4, 4, (void *)8, 1,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,4,8 expecting 3\n");
	t_taskpurge_x(1, 4, 7, NULL, 4, 4, (void *)8, 3,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,4,0 expecting 15\n");
	t_taskpurge_x(1, 4, 7, NULL, 4, 4, NULL, 15, &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,99,8 expecting 0\n");
	t_taskpurge_x(1, 4, 7, NULL, 99, 99, (void *)8, 0,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 3,5,0 expecting 5\n");
	t_taskpurge_x(1, 4, 7, &senders[3], 5, 5, 0, 5, &T13_nfails, &T13_nprobs, 1);


	t_info("testing purgerange on 2,4-5,8 expecting 2\n");
	t_taskpurge_x(1, 4, 7, &senders[2], 4, 5, (void *)8, 1,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,4-5,8 expecting 5\n");
	t_taskpurge_x(1, 4, 7, NULL, 4, 5, (void *)8, 5,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,5-6,0 expecting 28\n");
	t_taskpurge_x(1, 4, 7, NULL, 5, 6, NULL, 28, &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 0,99-101,8 expecting 0\n");
	t_taskpurge_x(1, 4, 7, NULL, 99, 101, (void *)8, 0,
		      &T13_nfails, &T13_nprobs, 1);


	t_info("testing purge on 3,5-6,0 expecting 10\n");
	t_taskpurge_x(1, 4, 7, &senders[3], 5, 6, NULL, 10, &T13_nfails,
		      &T13_nprobs, 1);

	result = T_UNRESOLVED;

	if ((T13_nfails == 0) && (T13_nprobs == 0))
		result = T_PASS;
	else if (T13_nfails)
		result = T_FAIL;

	return (result);
}
