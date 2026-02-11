evconnlistener_enable(struct evconnlistener *lev)
{
	int r;
	LOCK(lev);
	lev->enabled = 1;
	if (lev->cb)
		r = lev->ops->enable(lev);
	else
		r = 0;
	UNLOCK(lev);
	return r;
}
