startDataPump()
{
    Q_Q(FileCopyJob);


    m_canResume = false;
    m_resumeAnswerSent = false;
    m_getJob = 0L;
    m_putJob = put( m_dest, m_permissions, (m_flags | HideProgressInfo) );

    if ( m_modificationTime.isValid() ) {
        m_putJob->setModificationTime( m_modificationTime );
    }


    q->connect( m_putJob, SIGNAL(canResume(KIO::Job*,KIO::filesize_t)),
                SLOT(slotCanResume(KIO::Job*,KIO::filesize_t)));
    q->connect( m_putJob, SIGNAL(dataReq(KIO::Job*,QByteArray&)),
                SLOT(slotDataReq(KIO::Job*,QByteArray&)));
    q->addSubjob( m_putJob );
}
