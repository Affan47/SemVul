_fscache_invalidate_object(struct fscache_object *object,
							      int event)
{
	struct fscache_operation *op;
	struct fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x},%d", object->debug_id, event);


	if (!fscache_use_cookie(object)) {
		ASSERT(object->cookie->stores.rnode == NULL);
		set_bit(FSCACHE_OBJECT_RETIRED, &object->flags);
		_leave(" [no cookie]");
		return transit_to(KILL_OBJECT);
	}


	fscache_invalidate_writes(cookie);
	clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
	fscache_cancel_all_ops(object);


	op = kzalloc(sizeof(*op), GFP_KERNEL);
	if (!op)
		goto nomem;

	fscache_operation_init(op, object->cache->ops->invalidate_object,
			       NULL, NULL);
	op->flags = FSCACHE_OP_ASYNC |
		(1 << FSCACHE_OP_EXCLUSIVE) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);

	spin_lock(&cookie->lock);
	if (fscache_submit_exclusive_op(object, op) < 0)
		goto submit_op_failed;
	spin_unlock(&cookie->lock);
	fscache_put_operation(op);


	set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);


	if (test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);
	_leave(" [ok]");
	return transit_to(UPDATE_OBJECT);

nomem:
	fscache_mark_object_dead(object);
	fscache_unuse_cookie(object);
	_leave(" [ENOMEM]");
	return transit_to(KILL_OBJECT);

submit_op_failed:
	fscache_mark_object_dead(object);
	spin_unlock(&cookie->lock);
	fscache_unuse_cookie(object);
	kfree(op);
	_leave(" [EIO]");
	return transit_to(KILL_OBJECT);
}
