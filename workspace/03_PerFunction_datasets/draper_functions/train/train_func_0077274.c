urlResolveFinished( KJob * job )
{
    KIO::TransferJob *transferJob = dynamic_cast<KIO::TransferJob *>( job );

    if( transferJob && ( !( transferJob->isErrorPage() || job->error() ) ) )
    {
        m_resolvedChannelsToBeAdded.push_back( m_resolvedPodcasts.value( transferJob ) );
        m_resolvedPodcasts.remove( transferJob );
    }
    else
        requestUrlResolve( m_resolvedPodcasts.value( transferJob ) );

    if( m_resolvedPodcasts.empty() )
        continueDeviceUpdatesFinished();

    m_resolveUrlJob = 0;
}
