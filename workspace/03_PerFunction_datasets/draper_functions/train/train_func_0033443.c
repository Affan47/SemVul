t_timeout()
{

	if(!d->hostsToTry.isEmpty())
	{
		delete d->bs;
		d->bs = 0;

		d->aaaa = true;
		d->host = d->hostsToTry.takeFirst();
		do_resolve();
	}
}
