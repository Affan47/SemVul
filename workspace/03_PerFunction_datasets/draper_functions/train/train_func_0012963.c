__connman_notifier_proxy_changed(struct connman_service *service)
{
	GSList *list;

	for (list = notifier_list; list; list = list->next) {
		struct connman_notifier *notifier = list->data;

		if (notifier->proxy_changed)
			notifier->proxy_changed(service);
	}
}
