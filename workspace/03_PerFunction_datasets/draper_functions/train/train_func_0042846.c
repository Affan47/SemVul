uc_mgr_free_value(struct list_head *base)
{
	struct list_head *pos, *npos;
	struct ucm_value *val;

	list_for_each_safe(pos, npos, base) {
		val = list_entry(pos, struct ucm_value, list);
		free(val->name);
		free(val->data);
		list_del(&val->list);
		free(val);
	}
}
