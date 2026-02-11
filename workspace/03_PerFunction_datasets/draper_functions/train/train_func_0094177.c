dev_write(struct file *file, const char __user *u, size_t count,
			 loff_t *ppos)
{
	struct dlm_plock_info info;
	struct plock_op *op;
	int found = 0, do_callback = 0;

	if (count != sizeof(info))
		return -EINVAL;

	if (copy_from_user(&info, u, sizeof(info)))
		return -EFAULT;

	if (check_version(&info))
		return -EINVAL;

	spin_lock(&ops_lock);
	list_for_each_entry(op, &recv_list, list) {
		if (op->info.fsid == info.fsid &&
		    op->info.number == info.number &&
		    op->info.owner == info.owner) {
			struct plock_xop *xop = (struct plock_xop *)op;
			list_del_init(&op->list);
			memcpy(&op->info, &info, sizeof(info));
			if (xop->callback)
				do_callback = 1;
			else
				op->done = 1;
			found = 1;
			break;
		}
	}
	spin_unlock(&ops_lock);

	if (found) {
		if (do_callback)
			dlm_plock_callback(op);
		else
			wake_up(&recv_wq);
	} else
		log_print("dev_write no op %x %llx", info.fsid,
			  (unsigned long long)info.number);
	return count;
}
