end_log(struct lib_context *lc, struct list_head *log)
{
	struct list_head *pos, *tmp;

	list_for_each_safe(pos, tmp, log) {
		list_del(pos);
		dbg_free(list_entry(pos, struct change, changes));
	}
}
