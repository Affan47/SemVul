_sort_local_cluster(local_cluster_rec_t* rec_a,
			       local_cluster_rec_t* rec_b)
{
	if (rec_a->start_time < rec_b->start_time)
		return -1;
	else if (rec_a->start_time > rec_b->start_time)
		return 1;

	if (rec_a->preempt_cnt < rec_b->preempt_cnt)
		return -1;
	else if (rec_a->preempt_cnt > rec_b->preempt_cnt)
		return 1;

	if(!strcmp(local_cluster_name, rec_a->cluster_rec->name))
		return -1;
	else if(!strcmp(local_cluster_name, rec_b->cluster_rec->name))
		return 1;

	return 0;
}
