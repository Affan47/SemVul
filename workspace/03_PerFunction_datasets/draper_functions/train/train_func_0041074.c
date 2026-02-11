parseUrl(const QUrl &url)
{
#if defined(ADBLOCKSUBSCRIPTION_DEBUG)
    qDebug() << "AdBlockSubscription::" << __FUNCTION__ << url;
#endif
    if (url.scheme() != QLatin1String("abp"))
        return;
    if (url.path() != QLatin1String("subscribe"))
        return;

    m_title = QUrl::fromPercentEncoding(url.encodedQueryItemValue("title"));
    m_enabled = QUrl::fromPercentEncoding(url.encodedQueryItemValue("enabled")) != QLatin1String("false");
    m_location = QUrl::fromPercentEncoding(url.encodedQueryItemValue("location")).toUtf8();
    QByteArray lastUpdateByteArray = url.encodedQueryItemValue("lastUpdate");
    QString lastUpdateString = QUrl::fromPercentEncoding(lastUpdateByteArray);
    m_lastUpdate = QDateTime::fromString(lastUpdateString, Qt::ISODate);
    loadRules();
}
