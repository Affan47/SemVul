delete_listener(struct listener *listener)
{
	if (listener->state != LI_ASSIGNED)
		return;
	listener->state = LI_INIT;
	LIST_DEL(&listener->proto_list);
	listener->proto->nb_listeners--;
}
