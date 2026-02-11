partition_in_use(char *part_name)
{
	ListIterator job_iterator;
	struct job_record *job_ptr;
	struct part_record *part_ptr;

	part_ptr = find_part_record (part_name);
	if (part_ptr == NULL)
		return false;

	job_iterator = list_iterator_create(job_list);
	if (job_iterator == NULL)
		fatal("list_iterator_create: malloc failure");
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (job_ptr->part_ptr == part_ptr) {
			if (!IS_JOB_FINISHED(job_ptr)) {
				list_iterator_destroy(job_iterator);
				return true;
			}
		}
	}
	list_iterator_destroy(job_iterator);
	return false;
}
