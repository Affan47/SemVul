load(const KUrl &url)
    {
        m_jobdata.clear();

        kDebug(550) << "XmlLoader::load(): url: " << url;

        KIO::TransferJob *job = KIO::get(url, KIO::NoReload, KIO::HideProgressInfo);
        connect(job, SIGNAL(result(KJob*)),
                SLOT(slotJobResult(KJob*)));
        connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
                SLOT(slotJobData(KIO::Job*,QByteArray)));

        emit jobStarted(job);
    }
