resolveAsync()
{
	K_D;
	if (d->m_running) return;
	d->m_resolved = false;
        registerTypes();
	kDebug() << this << ":Starting resolve of : " << d->m_serviceName << " " << d->m_type << " " << d->m_domain << "\n";
	org::freedesktop::Avahi::Server s("org.freedesktop.Avahi","/",QDBusConnection::systemBus());

	QDBusReply<QDBusObjectPath> rep=s.ServiceResolverNew(-1, -1, d->m_serviceName, d->m_type,
	    domainToDNS(d->m_domain), -1, 8 );
	if (!rep.isValid()) {
	    emit resolved(false);
	    return;
	}

	org::freedesktop::Avahi::ServiceResolver *b=new org::freedesktop::Avahi::ServiceResolver("org.freedesktop.Avahi",rep.value().path(),
	    QDBusConnection::systemBus());
	connect(b,SIGNAL(Found(int,int,const QString &,const QString &,const QString &,const QString &, int, const QString &,ushort,
	     const QList<QByteArray>&, uint)),d, SLOT(gotFound(int,int,const QString &,const QString &,const QString &,const QString &,
	     int, const QString &,ushort , const QList<QByteArray>&, uint)));
	connect(b,SIGNAL(Failure(QString)),d, SLOT(gotError()));
	d->m_running=true;
}
