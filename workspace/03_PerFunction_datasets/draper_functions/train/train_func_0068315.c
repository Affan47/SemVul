rulesDownloaded()
{
#if defined(ADBLOCKSUBSCRIPTION_DEBUG)
    qDebug() << "AdBlockSubscription::" << __FUNCTION__ << rulesFileName();
#endif
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
#if defined(ADBLOCKSUBSCRIPTION_DEBUG)
        qDebug() << "AdBlockSubscription::" << __FUNCTION__ << "no reply?";
#endif
        return;
    }

    QByteArray response = reply->readAll();
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    reply->close();
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "AdBlockSubscription::" << __FUNCTION__ << "error" << reply->errorString();
        return;
    }

    if (redirect.isValid()) {
#if defined(ADBLOCKSUBSCRIPTION_DEBUG)
        qDebug() << "AdBlockSubscription::" << __FUNCTION__ << "redirect to:" << redirect;
#endif
        QNetworkRequest request(redirect);
        m_downloading = BrowserApplication::networkAccessManager()->get(request);
        connect(m_downloading, SIGNAL(finished()), this, SLOT(rulesDownloaded()));
        return;
    }

    if (response.isEmpty()) {
        qWarning() << "AdBlockSubscription::" << __FUNCTION__ << "empty response";
        return;
    }

    QString fileName = rulesFileName();
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite)) {
        qWarning() << "AdBlockSubscription::" << __FUNCTION__ << "Unable to open adblock file for writing:" << fileName;
        return;
    }
    file.write(response);
    m_lastUpdate = QDateTime::currentDateTime();
    loadRules();
    emit changed();
    m_downloading = 0;
}
