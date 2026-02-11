fetchBigPix()
{
    DEBUG_BLOCK
    CoverFoundItem *item = static_cast< CoverFoundItem* >( m_view->currentItem() );
    const KUrl url( item->metadata().value( "normalarturl" ) );
    if( !url.isValid() )
        return false;

    QNetworkReply *reply = The::networkAccessManager()->getData( url, this,
                           SLOT(handleFetchResult(KUrl,QByteArray,NetworkAccessManagerProxy::Error)) );
    m_urls.insert( url, item );

    if( !m_dialog )
    {
        m_dialog = new KProgressDialog( this );
        m_dialog.data()->setCaption( i18n( "Fetching Large Cover" ) );
        m_dialog.data()->setLabelText( i18n( "Download Progress" ) );
        m_dialog.data()->setModal( true );
        m_dialog.data()->setAllowCancel( true );
        m_dialog.data()->setAutoClose( false );
        m_dialog.data()->setAutoReset( true );
        m_dialog.data()->progressBar()->setMinimum( 0 );
        m_dialog.data()->setMinimumWidth( 300 );
        connect( reply, SIGNAL(downloadProgress(qint64,qint64)),
                        SLOT(downloadProgressed(qint64,qint64)) );
    }
    int result = m_dialog.data()->exec();
    bool success = (result == QDialog::Accepted) && !m_dialog.data()->wasCancelled();
    The::networkAccessManager()->abortGet( url );
    if( !success )
        m_urls.remove( url );
    m_dialog.data()->deleteLater();
    return success;
}
