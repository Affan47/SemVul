query_finished()
{
	JT_S5B *query = (JT_S5B *)sender();
	bool found = false;
	Entry* e;
	foreach(Entry* i, d->activeList) {
		if(i->query == query) {
			e = i;
			found = true;
			break;
		}
	}
	if(!found)
		return;
	e->query = 0;

#ifdef S5B_DEBUG
	printf("query finished: ");
#endif
	if(query->success()) {
		e->proxyInfo = query->proxyInfo();
#ifdef S5B_DEBUG
		printf("host/ip=[%s] port=[%d]\n", e->proxyInfo.host().toLatin1(), e->proxyInfo.port());
#endif
	}
	else {
#ifdef S5B_DEBUG
		printf("fail\n");
#endif
	}

	QPointer<QObject> self = this;
	e->c->proxyResult(query->success());
	if(!self)
		return;

	entryContinue(e);
}
