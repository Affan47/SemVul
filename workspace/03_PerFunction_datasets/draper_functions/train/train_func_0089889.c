swap_cgroup_swapon(int type, unsigned long max_pages)
{
	void *array;
	unsigned long array_size;
	unsigned long length;
	struct swap_cgroup_ctrl *ctrl;

	if (!do_swap_account)
		return 0;

	length = DIV_ROUND_UP(max_pages, SC_PER_PAGE);
	array_size = length * sizeof(void *);

	array = vzalloc(array_size);
	if (!array)
		goto nomem;

	ctrl = &swap_cgroup_ctrl[type];
	mutex_lock(&swap_cgroup_mutex);
	ctrl->length = length;
	ctrl->map = array;
	spin_lock_init(&ctrl->lock);
	if (swap_cgroup_prepare(type)) {

		ctrl->map = NULL;
		ctrl->length = 0;
		mutex_unlock(&swap_cgroup_mutex);
		vfree(array);
		goto nomem;
	}
	mutex_unlock(&swap_cgroup_mutex);

	return 0;
nomem:
	printk(KERN_INFO "couldn't allocate enough memory for swap_cgroup.\n");
	printk(KERN_INFO
		"swap_cgroup can be disabled by swapaccount=0 boot option\n");
	return -ENOMEM;
}
