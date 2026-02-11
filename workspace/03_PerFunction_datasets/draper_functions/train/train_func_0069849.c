ibnl_remove_client(int index)
{
	struct ibnl_client *cur, *next;

	mutex_lock(&ibnl_mutex);
	list_for_each_entry_safe(cur, next, &client_list, list) {
		if (cur->index == index) {
			list_del(&(cur->list));
			mutex_unlock(&ibnl_mutex);
			kfree(cur);
			return 0;
		}
	}
	pr_warn("Can't remove callback for client idx %d. Not found\n", index);
	mutex_unlock(&ibnl_mutex);

	return -EINVAL;
}
