nvif_notify_get(struct nvif_notify *notify)
{
	if (likely(notify->object) &&
	    !test_and_set_bit(NVIF_NOTIFY_USER, &notify->flags))
		return nvif_notify_get_(notify);
	return 0;
}
