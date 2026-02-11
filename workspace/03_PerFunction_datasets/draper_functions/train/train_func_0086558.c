blk_msg_write(struct file *filp, const char __user *buffer,
				size_t count, loff_t *ppos)
{
	char *msg;
	struct blk_trace *bt;

	if (count >= BLK_TN_MAX_MSG)
		return -EINVAL;

	msg = kmalloc(count + 1, GFP_KERNEL);
	if (msg == NULL)
		return -ENOMEM;

	if (copy_from_user(msg, buffer, count)) {
		kfree(msg);
		return -EFAULT;
	}

	msg[count] = '\0';
	bt = filp->private_data;
	__trace_note_message(bt, "%s", msg);
	kfree(msg);

	return count;
}
