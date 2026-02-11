badProxy( const QString &proxy )
{
  QDBusInterface( QL1S("org.kde.kded"), QL1S("/modules/proxyscout"))
      .asyncCall(QL1S("blackListProxy"), proxy);

  PRIVATE_DATA;
  const QStringList keys (d->cachedProxyData.keys());
  Q_FOREACH(const QString& key, keys) {
      d->cachedProxyData[key]->removeAddress(proxy);
  }
}
