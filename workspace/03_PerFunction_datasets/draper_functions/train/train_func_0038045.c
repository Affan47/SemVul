cleanup(void)
{
	int i;


	for (i = 0; i < NR_SLOTS; i++)
		if (map_id[i] > 0)
			shmctl(map_id[i], IPC_RMID, NULL);


	if (saved_nr_hugepages >= 0)
		setup_hugetlb_pool(saved_nr_hugepages);

	if (oc_pool > 0)
		restore_overcommit_pages(hpage_size, oc_pool);
}
