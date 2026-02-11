PR_RecordTraceEntries(
        void
)
{
    PRFileDesc  *logFile;
    PRInt32     lostSegments;
    PRInt32     currentSegment = 0;
    void        *buf;
    PRBool      doWrite;

    logFile = InitializeRecording();
    if ( logFile == NULL )
    {
        PR_LOG( lm, PR_LOG_DEBUG,
            ("PR_RecordTraceEntries: Failed to initialize"));
        return;
    }


    while ( logState != LogStop )
    {

        PR_Lock( logLock );

        while ( (logCount == 0) && ( logOrder == logState ) )
            PR_WaitCondVar( logCVar, PR_INTERVAL_NO_TIMEOUT );


        if ( logOrder != logState )
            ProcessOrders();


        if ( logCount )
        {
            lostSegments = logCount - logSegments;
            if ( lostSegments > 0 )
            {
                logLostData += ( logCount - logSegments );
                logCount = (logCount % logSegments);
                currentSegment = logCount;
                PR_LOG( lm, PR_LOG_DEBUG,
                    ("PR_RecordTraceEntries: LostData segments: %ld", logLostData));
            }
            else
            {
                logCount--;
            }

            buf = tBuf + ( logEntriesPerSegment * currentSegment );
            if (++currentSegment >= logSegments )
                currentSegment = 0;
            doWrite = PR_TRUE;
        }
        else
            doWrite = PR_FALSE;

        PR_Unlock( logLock );

        if ( doWrite == PR_TRUE )
        {
            if ( localState != LogSuspend )
                WriteTraceSegment( logFile, buf, logSegSize );
            else
                PR_LOG( lm, PR_LOG_DEBUG,
                    ("RecordTraceEntries: PR_Write(): is suspended" ));
        }

    }

    PR_Close( logFile );
    PR_LOG( lm, PR_LOG_DEBUG,
        ("RecordTraceEntries: exiting"));
    return;
}
