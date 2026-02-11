endOfData()
{
    Q_ASSERT( m_part );
    if ( m_isHTMLPart )
    {
        KHTMLPart* htmlPart = static_cast<KHTMLPart *>( static_cast<KParts::ReadOnlyPart *>( m_part ) );
        htmlPart->end();
    } else if ( m_tempFile )
    {
        const QString tempFileName = m_tempFile->fileName();
        m_tempFile->close();
        if ( m_partIsLoading )
        {


            kDebug() << "KMultiPart::endOfData part isn't ready, skipping frame";
            ++m_numberOfFramesSkipped;
            m_tempFile->setAutoRemove( true );
        }
        else
        {
            kDebug() << "KMultiPart::endOfData opening " << tempFileName;
            KUrl url(tempFileName);
            m_partIsLoading = true;
            (void) m_part->openUrl( url );
        }
        delete m_tempFile;
        m_tempFile = 0L;
    }
}
