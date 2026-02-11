afs_install_server(struct afs_server *server)
{
	struct afs_server *xserver;
	struct rb_node **pp, *p;
	int ret;

	_enter("%p", server);

	write_lock(&afs_servers_lock);

	ret = -EEXIST;
	pp = &afs_servers.rb_node;
	p = NULL;
	while (*pp) {
		p = *pp;
		_debug("- consider %p", p);
		xserver = rb_entry(p, struct afs_server, master_rb);
		if (server->addr.s_addr < xserver->addr.s_addr)
			pp = &(*pp)->rb_left;
		else if (server->addr.s_addr > xserver->addr.s_addr)
			pp = &(*pp)->rb_right;
		else
			goto error;
	}

	rb_link_node(&server->master_rb, p, pp);
	rb_insert_color(&server->master_rb, &afs_servers);
	ret = 0;

error:
	write_unlock(&afs_servers_lock);
	return ret;
}
