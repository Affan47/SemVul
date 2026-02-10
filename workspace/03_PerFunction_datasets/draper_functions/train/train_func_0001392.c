fsnotify_remove_first_event(struct fsnotify_group *group)
{
	struct fsnotify_event *event;

	BUG_ON(!mutex_is_locked(&group->notification_mutex));

	pr_debug("%s: group=%p\n", __func__, group);

	event = list_first_entry(&group->notification_list,
				 struct fsnotify_event, list);


	list_del_init(&event->list);
	group->q_len--;

	return event;
}
