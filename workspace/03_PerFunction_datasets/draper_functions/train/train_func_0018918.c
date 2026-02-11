slotApply()
{
    m_channel->setUrl( KUrl( m_ps->m_urlLineEdit->text() ) );
    m_channel->setAutoScan( m_ps->m_autoFetchCheck->isChecked() );
    m_channel->setFetchType(
        m_ps->m_downloadRadio->isChecked() ?
        Podcasts::PodcastChannel::DownloadWhenAvailable :
        Podcasts::PodcastChannel::StreamOrDownloadOnDemand
    );
    m_channel->setSaveLocation( m_ps->m_saveLocation->url() );

    m_channel->setPurge( m_ps->m_purgeCheck->isChecked() );
    m_channel->setPurgeCount( m_ps->m_purgeCountSpinBox->value() );
    m_channel->setWriteTags( m_ps->m_writeTagsCheck->isChecked() );

    enableButtonApply( false );
}
