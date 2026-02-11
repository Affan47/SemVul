slotRedirection(KIO::Job* job, const KUrl& u)
{
    if (!KAuthorized::authorizeUrlAction(QLatin1String("redirect"), url(), u)) {
        kWarning(7007) << "Redirection from" << url() << "to" << u << "REJECTED by policy!";
        setError(QNetworkReply::ContentAccessDenied, u.url());
        emit error(error());
        return;
    }
    setAttribute(QNetworkRequest::RedirectionTargetAttribute, QUrl(u));
    if (job->queryMetaData(QL1S("redirect-to-get")) == QL1S("true")) {
      setOperation(QNetworkAccessManager::GetOperation);
    }
}
