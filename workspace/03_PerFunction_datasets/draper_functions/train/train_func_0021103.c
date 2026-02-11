write(const QByteArray &buf)
{
	if(d->active)
		d->sock.write(buf);
}
