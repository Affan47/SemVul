readOutgoing(int *plainBytes)
{
	QByteArray a = d->to_net;
	d->to_net.clear();
	if(plainBytes)
		*plainBytes = d->to_net_encoded;
	d->layer.specifyEncoded(a.size(), d->to_net_encoded);
	d->to_net_encoded = 0;
	return a;
}
