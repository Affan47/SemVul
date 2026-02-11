writeData(const char *data, qint64 maxSize)
{
	if(isOpen() && !d->udp)
		return d->sock.write(data, maxSize);
	return 0;
}
