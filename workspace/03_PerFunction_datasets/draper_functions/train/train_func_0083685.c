pending_dispatch(struct pending_reply *pending,
			struct mrpc_message *msg)
{
	struct mrpc_event *event;

	if (pending->async) {
		event=mrpc_alloc_message_event(msg, EVENT_REPLY);
		event->callback=pending->data.async.callback;
		event->private=pending->data.async.private;
		queue_event(event);
	} else {

		g_atomic_pointer_set(pending->data.sync.reply, msg);
		sem_post(pending->data.sync.sem);
	}
	pending_free(pending);
}
