afs_proc_cells_write(struct file *file, const char __user *buf,
				    size_t size, loff_t *_pos)
{
	char *kbuf, *name, *args;
	int ret;


	if (size <= 1 || size >= PAGE_SIZE)
		return -EINVAL;

	kbuf = kmalloc(size + 1, GFP_KERNEL);
	if (!kbuf)
		return -ENOMEM;

	ret = -EFAULT;
	if (copy_from_user(kbuf, buf, size) != 0)
		goto done;
	kbuf[size] = 0;


	name = memchr(kbuf, '\n', size);
	if (name)
		*name = 0;


	name = strchr(kbuf, ' ');
	if (!name)
		goto inval;
	do {
		*name++ = 0;
	} while(*name == ' ');
	if (!*name)
		goto inval;

	args = strchr(name, ' ');
	if (!args)
		goto inval;
	do {
		*args++ = 0;
	} while(*args == ' ');
	if (!*args)
		goto inval;


	_debug("cmd=%s name=%s args=%s", kbuf, name, args);

	if (strcmp(kbuf, "add") == 0) {
		struct afs_cell *cell;

		cell = afs_cell_create(name, strlen(name), args, false);
		if (IS_ERR(cell)) {
			ret = PTR_ERR(cell);
			goto done;
		}

		afs_put_cell(cell);
		printk("kAFS: Added new cell '%s'\n", name);
	} else {
		goto inval;
	}

	ret = size;

done:
	kfree(kbuf);
	_leave(" = %d", ret);
	return ret;

inval:
	ret = -EINVAL;
	printk("kAFS: Invalid Command on /proc/fs/afs/cells file\n");
	goto done;
}
