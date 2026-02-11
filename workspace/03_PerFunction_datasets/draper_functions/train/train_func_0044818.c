slotResult(KJob *kJob)
{
    const int errcode = jobError(kJob);

    const QUrl redirectUrl = attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirectUrl.isValid()) {
        setAttribute(static_cast<QNetworkRequest::Attribute>(KIO::AccessManager::KioError), errcode);
        if (errcode && errcode != KIO::ERR_NO_CONTENT)
            emit error(error());
    }


    if (!m_metaDataRead) {
        readHttpResponseHeaders(qobject_cast<KIO::Job*>(kJob));
    }

    emitFinished(true);
}
