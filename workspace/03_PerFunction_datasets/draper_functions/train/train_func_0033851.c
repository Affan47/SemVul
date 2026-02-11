load()
{
#if defined(ADBLOCKMANAGER_DEBUG)
    qDebug() << "AdBlockManager::" << __FUNCTION__ << m_loaded;
#endif

    if (m_loaded)
        return;
    m_loaded = true;

    QSettings settings;
    settings.beginGroup(QLatin1String("AdBlock"));
    m_enabled = settings.value(QLatin1String("enabled"), m_enabled).toBool();

    QStringList defaultSubscriptions;
    defaultSubscriptions.append(QString::fromUtf8(customSubscriptionUrl().toEncoded()));
    defaultSubscriptions.append(QLatin1String("abp:subscribe?location=http://adblockplus.mozdev.org/easylist/easylist.txt&title=EasyList"));

    QStringList subscriptions = settings.value(QLatin1String("subscriptions"), defaultSubscriptions).toStringList();
    foreach (const QString &subscription, subscriptions) {
        QUrl url = QUrl::fromEncoded(subscription.toUtf8());
        AdBlockSubscription *adBlockSubscription = new AdBlockSubscription(url, this);
        connect(adBlockSubscription, SIGNAL(rulesChanged()), this, SIGNAL(rulesChanged()));
        connect(adBlockSubscription, SIGNAL(changed()), this, SIGNAL(rulesChanged()));
        m_subscriptions.append(adBlockSubscription);
    }
}
