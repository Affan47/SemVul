serio_raw_open(struct inode *inode, struct file *file)
{
	struct serio_raw *serio_raw;
	struct serio_raw_client *client;
	int retval;

	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		return retval;

	serio_raw = serio_raw_locate(iminor(inode));
	if (!serio_raw) {
		retval = -ENODEV;
		goto out;
	}

	if (serio_raw->dead) {
		retval = -ENODEV;
		goto out;
	}

	client = kzalloc(sizeof(struct serio_raw_client), GFP_KERNEL);
	if (!client) {
		retval = -ENOMEM;
		goto out;
	}

	client->serio_raw = serio_raw;
	file->private_data = client;

	kref_get(&serio_raw->kref);

	serio_pause_rx(serio_raw->serio);
	list_add_tail(&client->node, &serio_raw->client_list);
	serio_continue_rx(serio_raw->serio);

out:
	mutex_unlock(&serio_raw_mutex);
	return retval;
}
