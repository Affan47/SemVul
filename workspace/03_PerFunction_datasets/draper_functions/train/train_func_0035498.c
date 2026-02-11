t_pool_delete_result(t_pool_result *r, int free_data) {
    if (!r)
	return;

    if (free_data && r->data)
	free(r->data);

    free(r);
}
