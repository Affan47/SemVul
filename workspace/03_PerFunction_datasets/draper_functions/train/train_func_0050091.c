addData( KIO::Job *job, const QByteArray &data )
{
    if( !data.size() )
    {
        return;
    }

    struct PodcastEpisodeDownload &download = m_downloadJobMap[job];


    if( !download.finalNameReady )
    {
        download.finalNameReady = true;
        if( checkEnclosureLocallyAvailable( job ) )
            return;
    }

    if( download.tmpFile->write( data ) == -1 )
    {
        error() << "write error for " << download.tmpFile->fileName() << ": "
                << download.tmpFile->errorString();
        job->kill();
    }
}
