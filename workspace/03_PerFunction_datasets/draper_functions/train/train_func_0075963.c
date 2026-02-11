metaDataChanged()
{
    QVariant locationHeader = m_reply->header(QNetworkRequest::LocationHeader);
    if (locationHeader.isValid()) {
        m_url = locationHeader.toUrl();
        m_reply->deleteLater();
        m_reply = BrowserApplication::networkAccessManager()->get(QNetworkRequest(m_url));
        init();
        return;
    }

#ifdef DOWNLOADMANAGER_DEBUG
    qDebug() << "DownloadItem::" << __FUNCTION__ << "not handled.";
#endif
}
