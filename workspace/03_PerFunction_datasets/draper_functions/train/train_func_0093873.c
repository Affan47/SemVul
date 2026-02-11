reset()
{
	d->m->unlink(this);

	delete d->ft;
	d->ft = 0;

	delete d->c;
	d->c = 0;

	d->state = Idle;
	d->needStream = false;
	d->sent = 0;
	d->sender = false;
}
