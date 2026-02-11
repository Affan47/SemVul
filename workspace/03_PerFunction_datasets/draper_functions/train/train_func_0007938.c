run()
{
	d->m.lock();
	d->loop = new QEventLoop;
	d->agent = new SyncThreadAgent;
	connect(d->agent, SIGNAL(started()), d, SLOT(agent_started()), Qt::DirectConnection);
	connect(d->agent, SIGNAL(call_ret(bool, const QVariant &)), d, SLOT(agent_call_ret(bool, const QVariant &)), Qt::DirectConnection);
	d->loop->exec();
	d->m.lock();
	atEnd();
	delete d->agent;
	delete d->loop;
	d->agent = 0;
	d->loop = 0;
	d->w.wakeOne();
	d->m.unlock();
}
