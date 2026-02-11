fanotify_get_response(struct fsnotify_group *group,
				 struct fanotify_perm_event_info *event)
{
	int ret;

	pr_debug("%s: group=%p event=%p\n", __func__, group, event);

	wait_event(group->fanotify_data.access_waitq, event->response);


	switch (event->response) {
	case FAN_ALLOW:
		ret = 0;
		break;
	case FAN_DENY:
	default:
		ret = -EPERM;
	}
	event->response = 0;

	pr_debug("%s: group=%p event=%p about to return ret=%d\n", __func__,
		 group, event, ret);

	return ret;
}
