ss_incomingUDP(const QString &host, int port, const QHostAddress &addr, int sourcePort, const QByteArray &data)
{
	if(port != 0 || port != 1)
		return;

	foreach(S5BManager* m, d->manList) {
		if(m->srv_ownsHash(host)) {
			m->srv_incomingUDP(port == 1 ? true : false, addr, sourcePort, host, data);
			return;
		}
	}
}
