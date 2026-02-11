deserializeProxy(const QString &serializedString, QNetworkProxy &proxy)
{
    QString t = Utils::decrypt(serializedString.toUtf8(), "ProXySeTtInGs");
    QStringList l = t.split(::SERIALIZER_SEPARATOR);
    if (l.count() != 5)
        return false;
    proxy.setType(QNetworkProxy::ProxyType(l.value(0).toInt()));
    proxy.setHostName(l.value(1));
    proxy.setPort(l.value(2).toInt());
    proxy.setUser(l.value(3));
    proxy.setPassword(l.value(4));
    return true;
}
