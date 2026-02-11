_k_slotResult(KJob *job)
{
    if ( job->error() != 0)
    {
        q->error( job->error(), job->errorText() );
    }
    else
    {
        KIO::StatJob *stat_job = qobject_cast<KIO::StatJob *>(job);
        if ( stat_job!=0L )
        {
            KIO::UDSEntry entry = stat_job->statResult();
	    q->prepareUDSEntry(entry);
            q->statEntry( entry );
        }
        q->finished();
    }

    eventLoop.exit();
}
