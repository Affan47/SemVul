save()
{
#if defined(ADBLOCKMANAGER_DEBUG)
    qDebug() << "AdBlockManager::" << __FUNCTION__ << m_loaded;
#endif
    if (!m_loaded)
        return;

    QSettings settings;
    settings.beginGroup(QLatin1String("AdBlock"));
    settings.setValue(QLatin1String("enabled"), m_enabled);
    QStringList subscriptions;
    foreach (AdBlockSubscription *subscription, m_subscriptions) {
        if (!subscription)
            continue;
        subscriptions.append(QString::fromUtf8(subscription->url().toEncoded()));
        subscription->saveRules();
    }
    settings.setValue(QLatin1String("subscriptions"), subscriptions);
}
