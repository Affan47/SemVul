downloadPayload(Entry *entry)
{
    if(!entry) {
        emit signalPayloadFailed(entry);
        return;
    }
    KUrl source = KUrl(entry->payload().representation());

    if (!source.isValid()) {
        kError() << "The entry doesn't have a payload." << endl;
        emit signalPayloadFailed(entry);
        return;
    }

    if (m_installation->isRemote()) {


        entry->setStatus(Entry::Installed);
        m_payloadfiles[entry] = entry->payload().representation();
        install(source.pathOrUrl());
        emit signalPayloadLoaded(source);

        return;
    }

    KUrl destination = QString(KGlobal::dirs()->saveLocation("tmp") + KRandom::randomString(10));
    kDebug() << "Downloading payload '" << source << "' to '" << destination << "'";


    KIO::FileCopyJob *job = KIO::file_copy(source, destination, -1, KIO::Overwrite | KIO::HideProgressInfo);
    connect(job,
            SIGNAL(result(KJob*)),
            SLOT(slotPayloadResult(KJob*)));
    connect(job,
            SIGNAL(percent(KJob*,ulong)),
            SLOT(slotProgress(KJob*,ulong)));

    m_entry_jobs[job] = entry;
}
