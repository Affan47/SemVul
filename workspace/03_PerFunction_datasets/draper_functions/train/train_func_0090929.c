foundMimeType(const QString& type)
{
    kDebug(7010) << "Resulting mime type is " << type;

    KIO::TransferJob *job = qobject_cast<KIO::TransferJob *>(d->m_job);
    if (job) {

        setUrl( job->url() );

        job->putOnHold();
        KIO::Scheduler::publishSlaveOnHold();
        d->m_job = 0;
    }

    Q_ASSERT(!d->m_bFinished);


    if (!d->m_preferredService.isEmpty()) {
        kDebug(7010) << "Attempting to open with preferred service: " << d->m_preferredService;
        KService::Ptr serv = KService::serviceByDesktopName(d->m_preferredService);
        if (serv && serv->hasMimeType(type)) {
            KUrl::List lst;
            lst.append(d->m_strURL);
            if (KRun::run(*serv, lst, d->m_window, false, QString(), d->m_asn)) {
                setFinished(true);
                return;
            }


        }
    }


    KMimeType::Ptr mime = KMimeType::mimeType(type, KMimeType::ResolveAliases);
    if (!mime) {
        kWarning(7010) << "Unknown mimetype " << type;
    }
    if (mime && mime->is("application/x-desktop") && !d->m_localPath.isEmpty()) {
        d->m_strURL = KUrl();
        d->m_strURL.setPath(d->m_localPath);
    }

    if (!KRun::runUrl(d->m_strURL, type, d->m_window, false , d->m_runExecutables, d->m_suggestedFileName, d->m_asn)) {
        d->m_bFault = true;
    }
    setFinished(true);
}
