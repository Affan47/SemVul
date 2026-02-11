load(const QString &providersurl)
{


    m_providers.clear();
    m_jobdata.clear();


    KIO::TransferJob *job = KIO::get(KUrl(providersurl), KIO::NoReload, KIO::HideProgressInfo);
    connect(job, SIGNAL(result(KJob*)),
            SLOT(slotJobResult(KJob*)));
    connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
            SLOT(slotJobData(KIO::Job*,QByteArray)));
}
