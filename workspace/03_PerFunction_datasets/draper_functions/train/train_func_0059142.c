deallocate_lists(void)
{
	int i;

	for (i = 0; i < nic_cnt; i++)
		free(nic_list[i]);

	nic_cnt = 0;
	for (i = 0; i < tgt_cnt; i++)
		free(target_list[i]);

	tgt_cnt = 0;

}
