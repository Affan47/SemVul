shmem_exit(int code)
{
	elog(DEBUG3, "shmem_exit(%d)", code);


	while (--on_shmem_exit_index >= 0)
		(*on_shmem_exit_list[on_shmem_exit_index].function) (code,
								on_shmem_exit_list[on_shmem_exit_index].arg);

	on_shmem_exit_index = 0;
}
