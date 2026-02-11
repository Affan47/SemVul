reset(bool clear)
{
	if(d->http.isActive())
		d->http.stop();
	if(clear)
		clearReadBuffer();
	clearWriteBuffer();
	d->out.resize(0);
	d->state = 0;
	d->closing = false;
	d->t->stop();
}
