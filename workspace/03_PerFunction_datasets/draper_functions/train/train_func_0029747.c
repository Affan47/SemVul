nvif_notify(const void *header, u32 length, const void *data, u32 size)
{
	struct nvif_notify *notify = NULL;
	const union {
		struct nvif_notify_rep_v0 v0;
	} *args = header;
	int ret = NVIF_NOTIFY_DROP;

	if (length == sizeof(args->v0) && args->v0.version == 0) {
		if (WARN_ON(args->v0.route))
			return NVIF_NOTIFY_DROP;
		notify = (void *)(unsigned long)args->v0.token;
	}

	if (!WARN_ON(notify == NULL)) {
		struct nvif_client *client = notify->object->client;
		if (!WARN_ON(notify->size != size)) {
			atomic_inc(&notify->putcnt);
			if (test_bit(NVIF_NOTIFY_WORK, &notify->flags)) {
				memcpy((void *)notify->data, data, size);
				schedule_work(&notify->work);
				return NVIF_NOTIFY_DROP;
			}
			notify->data = data;
			ret = nvif_notify_func(notify, client->driver->keep);
			notify->data = NULL;
		}
	}

	return ret;
}
