_do_fdump(List job_info_list, int lc)
{
	filetxt_jobcomp_info_t *jobcomp_info = NULL;
	ListIterator itr = list_iterator_create(job_info_list);

	printf("\n------- Line %d -------\n", lc);
	while((jobcomp_info = list_next(itr))) {
		printf("%12s: %s\n", jobcomp_info->name, jobcomp_info->val);
	}
}
