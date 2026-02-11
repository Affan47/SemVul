slotCopyFinished( KJob * job )
{
    kDebug(250) << "KFilePropsPlugin::slotCopyFinished";
    if (job)
    {

        emit leaveModality();
        if ( job->error() )
        {
            job->uiDelegate()->showErrorMessage();

            properties->updateUrl( static_cast<KIO::CopyJob*>(job)->srcUrls().first() );
            properties->abortApplying();
            return;
        }
    }

    Q_ASSERT( !properties->item().isNull() );
    Q_ASSERT( !properties->item().url().isEmpty() );


    if (d->bDesktopFile && !d->m_sRelativePath.isEmpty())
    {
        kDebug(250) << "KFilePropsPlugin::slotCopyFinished " << d->m_sRelativePath;
        KUrl newURL;
        newURL.setPath( KDesktopFile::locateLocal(d->m_sRelativePath) );
        kDebug(250) << "KFilePropsPlugin::slotCopyFinished path=" << newURL.path();
        properties->updateUrl( newURL );
    }

    if ( d->bKDesktopMode && d->bDesktopFile ) {


        if ( d->m_bFromTemplate ) {
            KIO::UDSEntry entry;
            KIO::NetAccess::stat( properties->kurl(), entry, 0 );
            KFileItem item( entry, properties->kurl() );
            KDesktopFile config( item.localPath() );
            KConfigGroup cg = config.desktopGroup();
            QString nameStr = nameFromFileName(properties->kurl().fileName());
            cg.writeEntry( "Name", nameStr );
            cg.writeEntry( "Name", nameStr, KConfigGroup::Persistent|KConfigGroup::Localized);
        }
    }

    if (d->m_linkTargetLineEdit && !d->bMultiple) {
        const KFileItem item = properties->item();
        const QString newTarget = d->m_linkTargetLineEdit->text();
        if (newTarget != item.linkDest()) {
            kDebug(250) << "Updating target of symlink to" << newTarget;
            KIO::Job* job = KIO::symlink(newTarget, item.url(), KIO::Overwrite);
            job->ui()->setAutoErrorHandlingEnabled(true);
            job->exec();
        }
    }


    if ( d->m_bFromTemplate ) {

        KDesktopFile templateResult ( static_cast<KIO::CopyJob*>(job)->srcUrls().first().toLocalFile() );
        if ( templateResult.hasApplicationType() ) {


            KFileItem appLink ( properties->item() );
            KFileItemList fileItemList;
            fileItemList << appLink;


            KIO::Job* chmodJob = KIO::chmod( fileItemList, 0100, 0100, QString(), QString(), KIO::HideProgressInfo );
            chmodJob->exec();
        }
    }
}
