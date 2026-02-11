config_ptoken_alloc(void)
{
	struct ptoken *ret_val = malloc(sizeof(*ret_val));

	if(ret_val) {
		memset(ret_val, 0, sizeof(*ret_val));
		INIT_LIST_HEAD(&ret_val->list);
		INIT_LIST_HEAD(&ret_val->args);
	}
	return ret_val;
}
