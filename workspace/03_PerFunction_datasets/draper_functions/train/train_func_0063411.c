con_connect(S5BConnection *c)
{
	if(findEntry(c))
		return;
	Entry *e = new Entry;
	e->c = c;
	e->sid = c->d->sid;
	d->activeList.append(e);

	if(c->d->proxy.isValid()) {
		queryProxy(e);
		return;
	}
	entryContinue(e);
}
