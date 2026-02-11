ocfs2_loaded_cluster_plugins_show(struct kobject *kobj,
						 struct kobj_attribute *attr,
						 char *buf)
{
	ssize_t ret = 0, total = 0, remain = PAGE_SIZE;
	struct ocfs2_stack_plugin *p;

	spin_lock(&ocfs2_stack_lock);
	list_for_each_entry(p, &ocfs2_stack_list, sp_list) {
		ret = snprintf(buf, remain, "%s\n",
			       p->sp_name);
		if (ret < 0) {
			total = ret;
			break;
		}
		if (ret == remain) {

			total = -E2BIG;
			break;
		}
		total += ret;
		remain -= ret;
	}
	spin_unlock(&ocfs2_stack_lock);

	return total;
}
