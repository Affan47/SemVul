dump_results(struct sa_query_result *r, void (*dump_func) (void *))
{
	unsigned i;
	for (i = 0; i < r->result_cnt; i++) {
		void *data = sa_get_query_rec(r->p_result_madw, i);
		dump_func(data);
	}
}
