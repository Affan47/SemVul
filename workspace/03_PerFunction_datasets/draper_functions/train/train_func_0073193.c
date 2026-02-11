readUnprocessed()
{
	if(d->mode == Stream)
	{
		QByteArray a = d->unprocessed;
		d->unprocessed.clear();
		return a;
	}
	else
		return QByteArray();
}
