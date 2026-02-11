fanotify_read(struct file *file, char __user *buf,
			     size_t count, loff_t *pos)
{
	struct fsnotify_group *group;
	struct fsnotify_event *kevent;
	char __user *start;
	int ret;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	start = buf;
	group = file->private_data;

	pr_debug("%s: group=%p\n", __func__, group);

	add_wait_queue(&group->notification_waitq, &wait);
	while (1) {
		mutex_lock(&group->notification_mutex);
		kevent = get_one_event(group, count);
		mutex_unlock(&group->notification_mutex);

		if (IS_ERR(kevent)) {
			ret = PTR_ERR(kevent);
			break;
		}

		if (!kevent) {
			ret = -EAGAIN;
			if (file->f_flags & O_NONBLOCK)
				break;

			ret = -ERESTARTSYS;
			if (signal_pending(current))
				break;

			if (start != buf)
				break;

			wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
			continue;
		}

		ret = copy_event_to_user(group, kevent, buf);


		if (!(kevent->mask & FAN_ALL_PERM_EVENTS)) {
			fsnotify_destroy_event(group, kevent);
			if (ret < 0)
				break;
		} else {
#ifdef CONFIG_FANOTIFY_ACCESS_PERMISSIONS
			if (ret < 0) {
				FANOTIFY_PE(kevent)->response = FAN_DENY;
				wake_up(&group->fanotify_data.access_waitq);
				break;
			}
			spin_lock(&group->fanotify_data.access_lock);
			list_add_tail(&kevent->list,
				      &group->fanotify_data.access_list);
			spin_unlock(&group->fanotify_data.access_lock);
#endif
		}
		buf += ret;
		count -= ret;
	}
	remove_wait_queue(&group->notification_waitq, &wait);

	if (start != buf && ret != -EFAULT)
		ret = buf - start;
	return ret;
}
