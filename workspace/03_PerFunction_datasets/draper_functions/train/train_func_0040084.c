dm_unregister_target(struct target_type *tt)
{
	down_write(&_lock);
	if (!__find_target_type(tt->name)) {
		DMCRIT("Unregistering unrecognised target: %s", tt->name);
		BUG();
	}

	list_del(&tt->list);

	up_write(&_lock);
}
