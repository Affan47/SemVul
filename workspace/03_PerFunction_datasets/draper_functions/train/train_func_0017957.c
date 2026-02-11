workflow()
{
    disconnect(this, 0, this, 0);
    if ((m_command == command_upload) || (m_command == command_download)) {
        connect(this,
                SIGNAL(signalProviderLoaded(KNS::Provider*)),
                SLOT(slotProviderLoaded(KNS::Provider*)));
    }

    if (m_command == command_upload) {
        connect(this,
                SIGNAL(signalProvidersFinished()),
                SLOT(slotHandleUpload()));
        connect(this,
                SIGNAL(signalProvidersFailed()),
                SLOT(stopLoop()));

        m_uploadedEntry = NULL;
    }

    if (m_command == command_download) {
        m_downloaddialog = new DownloadDialog(this, m_parent);

        s_dialogs.insert(componentName(), m_downloaddialog);

        connect(this, SIGNAL(signalEntriesFinished()),
                SLOT(slotEntriesFinished()));
        connect(this,
                SIGNAL(signalEntryChanged(KNS::Entry*)),
                SLOT(slotEntryChanged(KNS::Entry*)));
        connect(this,
                SIGNAL(signalProvidersFailed()),
                SLOT(slotDownloadDialogClosed()));
        connect(m_downloaddialog,
                SIGNAL(destroyed(QObject*)),
                SLOT(slotDownloadDialogDestroyed()));
        connect(m_downloaddialog, SIGNAL(finished()), SLOT(slotDownloadDialogClosed()));


        m_downloaddialog->show();
    }

    start();

    if (m_modal) {
        QEventLoop loop;
        m_loop = &loop;
        loop.exec();
    }
}
