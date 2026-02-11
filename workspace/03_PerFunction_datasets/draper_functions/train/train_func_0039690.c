insertData(const QByteArray &a)
{
	if(!a.isEmpty()) {
		if (!d->layers.isEmpty()) {
			SecureLayer *s = d->layers.last();
			s->writeIncoming(a);
		}
		else {
			incomingData(a);
		}
	}
}
