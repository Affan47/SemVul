uc_mgr_free_dev_list(struct list_head *base)
{
	struct list_head *pos, *npos;
	struct dev_list *dlist;

	list_for_each_safe(pos, npos, base) {
		dlist = list_entry(pos, struct dev_list, list);
		free(dlist->name);
		list_del(&dlist->list);
		free(dlist);
	}
}
