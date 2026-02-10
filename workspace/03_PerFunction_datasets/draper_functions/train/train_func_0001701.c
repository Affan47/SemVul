pcmcia_release_window(struct pcmcia_device *p_dev, struct resource *res)
{
	struct pcmcia_socket *s = p_dev->socket;
	pccard_mem_map *win;
	unsigned int w;

	dev_dbg(&p_dev->dev, "releasing window %pR\n", res);

	w = ((res->flags & IORESOURCE_BITS & WIN_FLAGS_REQ) >> 2) - 1;
	if (w >= MAX_WIN)
		return -EINVAL;

	mutex_lock(&s->ops_mutex);
	win = &s->win[w];

	if (!(p_dev->_win & CLIENT_WIN_REQ(w))) {
		dev_dbg(&p_dev->dev, "not releasing unknown window\n");
		mutex_unlock(&s->ops_mutex);
		return -EINVAL;
	}


	win->flags &= ~MAP_ACTIVE;
	s->ops->set_mem_map(s, win);
	s->state &= ~SOCKET_WIN_REQ(w);


	if (win->res) {
		release_resource(res);
		release_resource(win->res);
		kfree(win->res);
		win->res = NULL;
	}
	res->start = res->end = 0;
	res->flags = IORESOURCE_MEM;
	p_dev->_win &= ~CLIENT_WIN_REQ(w);
	mutex_unlock(&s->ops_mutex);

	return 0;
}
