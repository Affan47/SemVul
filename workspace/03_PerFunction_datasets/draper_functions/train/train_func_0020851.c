setOptProbe(bool b)
{
#ifdef XMPP_DEBUG
	XDEBUG << "b:" << b;
#endif

	if(d->mode != Idle)
		return;
	d->opt_ssl = (b ? Probe : Never);
}
