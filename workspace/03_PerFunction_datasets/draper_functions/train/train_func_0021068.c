fscache_enqueue_dependents(struct fscache_object *object, int event)
{
	struct fscache_object *dep;
	bool ret = true;

	_enter("{OBJ%x}", object->debug_id);

	if (list_empty(&object->dependents))
		return true;

	spin_lock(&object->lock);

	while (!list_empty(&object->dependents)) {
		dep = list_entry(object->dependents.next,
				 struct fscache_object, dep_link);
		list_del_init(&dep->dep_link);

		fscache_raise_event(dep, event);
		fscache_put_object(dep);

		if (!list_empty(&object->dependents) && need_resched()) {
			ret = false;
			break;
		}
	}

	spin_unlock(&object->lock);
	return ret;
}
