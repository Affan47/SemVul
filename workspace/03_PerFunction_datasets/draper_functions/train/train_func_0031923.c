slotResult( KJob *job )
{
    Q_D(PreviewJob);

    removeSubjob(job);
    Q_ASSERT ( !hasSubjobs() );
    switch ( d->state )
    {
        case PreviewJobPrivate::STATE_STATORIG:
        {
            if (job->error())
            {

                d->determineNextFile();
                return;
            }
            const KIO::UDSEntry entry = static_cast<KIO::StatJob*>(job)->statResult();
            d->tOrig = entry.numberValue( KIO::UDSEntry::UDS_MODIFICATION_TIME, 0 );

            bool skipCurrentItem = false;
            const KIO::filesize_t size = (KIO::filesize_t)entry.numberValue( KIO::UDSEntry::UDS_SIZE, 0 );
            const KUrl itemUrl = d->currentItem.item.mostLocalUrl();

            if (itemUrl.isLocalFile() || KProtocolInfo::protocolClass(itemUrl.protocol()) == QLatin1String(":local"))
            {
                skipCurrentItem = !d->ignoreMaximumSize && size > d->maximumLocalSize
                                  && !d->currentItem.plugin->property("IgnoreMaximumSize").toBool();
            }
            else
            {

                skipCurrentItem = !d->ignoreMaximumSize && size > d->maximumRemoteSize;


                if (!skipCurrentItem) {

                    KMimeType::Ptr mime = d->currentItem.item.mimeTypePtr();
                    if (mime && mime->is("inode/directory")) {
                        skipCurrentItem = true;
                    }
                }
            }
            if (skipCurrentItem)
            {
                d->determineNextFile();
                return;
            }

            bool pluginHandlesSequences = d->currentItem.plugin->property("HandleSequences", QVariant::Bool).toBool();
            if ( !d->currentItem.plugin->property( "CacheThumbnail" ).toBool()  || (d->sequenceIndex && pluginHandlesSequences) )
            {


                d->getOrCreateThumbnail();
                return;
            }

            if ( d->statResultThumbnail() )
                return;

            d->getOrCreateThumbnail();
            return;
        }
        case PreviewJobPrivate::STATE_GETORIG:
        {
            if (job->error())
            {
                d->determineNextFile();
                return;
            }

            d->createThumbnail( static_cast<KIO::FileCopyJob*>(job)->destUrl().toLocalFile() );
            return;
        }
        case PreviewJobPrivate::STATE_CREATETHUMB:
        {
            if (!d->tempName.isEmpty())
            {
                QFile::remove(d->tempName);
                d->tempName.clear();
            }
            d->determineNextFile();
            return;
        }
    }
}
