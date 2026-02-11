setUsername(const QString &username)
{
	d->user = username;
	if(d->pool)
		d->pool->setUsername(d->user);
}
