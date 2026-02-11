setPassword(const QString &s)
{
	if(d->client.old) {
		d->client.setPassword(s);
	}
	else {
		if(d->sasl)
			d->sasl->setPassword(QCA::SecureArray(s.toUtf8()));
	}
}
