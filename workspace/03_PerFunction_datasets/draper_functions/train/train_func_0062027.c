hasChanged()
{
    bool fetchTypeChanged = true;

    if( ( m_ps->m_streamRadio->isChecked() && m_channel->fetchType() == Podcasts::PodcastChannel::StreamOrDownloadOnDemand ) ||
        ( m_ps->m_downloadRadio->isChecked() && m_channel->fetchType() == Podcasts::PodcastChannel::DownloadWhenAvailable ) )
    {
        fetchTypeChanged = false;
    }

    return( m_channel->url() != m_ps->m_urlLineEdit->text() ||
            m_channel->saveLocation() != m_ps->m_saveLocation->url() ||
            m_channel->autoScan() != m_ps->m_autoFetchCheck->isChecked() ||
            m_channel->hasPurge() != m_ps->m_purgeCheck->isChecked()     ||
            m_channel->purgeCount() != m_ps->m_purgeCountSpinBox->value() ||
            fetchTypeChanged ||
            m_channel->writeTags() != m_ps->m_writeTagsCheck->isChecked()
          );
}
