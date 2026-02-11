afs_do_give_up_callback(struct afs_server *server,
				    struct afs_vnode *vnode)
{
	struct afs_callback *cb;

	_enter("%p,%p", server, vnode);

	cb = &server->cb_break[server->cb_break_head];
	cb->fid		= vnode->fid;
	cb->version	= vnode->cb_version;
	cb->expiry	= vnode->cb_expiry;
	cb->type	= vnode->cb_type;
	smp_wmb();
	server->cb_break_head =
		(server->cb_break_head + 1) &
		(ARRAY_SIZE(server->cb_break) - 1);


	switch (atomic_inc_return(&server->cb_break_n)) {
	case 1 ... AFSCBMAX - 1:
		queue_delayed_work(afs_callback_update_worker,
				   &server->cb_break_work, HZ * 2);
		break;
	case AFSCBMAX:
		afs_flush_callback_breaks(server);
		break;
	default:
		break;
	}

	ASSERT(server->cb_promises.rb_node != NULL);
	rb_erase(&vnode->cb_promise, &server->cb_promises);
	vnode->cb_promised = false;
	_leave("");
}
