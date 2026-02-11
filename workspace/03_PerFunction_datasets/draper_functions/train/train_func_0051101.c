sync_timeline_free(struct kref *kref)
{
	struct sync_timeline *obj =
		container_of(kref, struct sync_timeline, kref);

	sync_timeline_debug_remove(obj);

	if (obj->ops->release_obj)
		obj->ops->release_obj(obj);

	kfree(obj);
}
