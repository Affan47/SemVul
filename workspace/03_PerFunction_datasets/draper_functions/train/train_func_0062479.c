free_members(struct call_queue *q, int all)
{

	struct member *cur;
	struct ao2_iterator mem_iter = ao2_iterator_init(q->members, 0);

	while ((cur = ao2_iterator_next(&mem_iter))) {
		if (all || !cur->dynamic) {
			member_remove_from_queue(q, cur);
		}
		ao2_ref(cur, -1);
	}
	ao2_iterator_destroy(&mem_iter);
}
