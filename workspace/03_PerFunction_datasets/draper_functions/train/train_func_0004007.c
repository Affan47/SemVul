reset()
{
	d->t.stop();
	delete d->active_udp;
	d->active_udp = 0;
	delete d->active;
	d->active = 0;
	while (!d->itemList.empty()) {
		delete d->itemList.takeFirst();
	}
}
