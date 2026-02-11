RunTCP( void ) {
    unsigned long currLen = 0;
    struct itimerval it;
    max_size_t totLen = 0;

    int err;

    char* readAt = mBuf;


    bool canRead = true, mMode_Time = isModeTime( mSettings );

    ReportStruct *reportstruct = NULL;


    mSettings->reporthdr = InitReport( mSettings );
    reportstruct = new ReportStruct;
    reportstruct->packetID = 0;

    lastPacketTime.setnow();
    if ( mMode_Time ) {
	memset (&it, 0, sizeof (it));
	it.it_value.tv_sec = (int) (mSettings->mAmount / 100.0);
	it.it_value.tv_usec = (int) 10000 * (mSettings->mAmount -
	    it.it_value.tv_sec * 100.0);
	err = setitimer( ITIMER_REAL, &it, NULL );
	if ( err != 0 ) {
	    perror("setitimer");
	    exit(1);
	}
    }
    do {


        if ( isFileInput( mSettings ) ) {
            Extractor_getNextDataBlock( readAt, mSettings );
            canRead = Extractor_canRead( mSettings ) != 0;
        } else
            canRead = true;


        currLen = write( mSettings->mSock, mBuf, mSettings->mBufLen );
        if ( currLen < 0 ) {
            WARN_errno( currLen < 0, "write2" );
            break;
        }
	totLen += currLen;

	if(mSettings->mInterval > 0) {
    	    gettimeofday( &(reportstruct->packetTime), NULL );
            reportstruct->packetLen = currLen;
            ReportPacket( mSettings->reporthdr, reportstruct );
        }

        if ( !mMode_Time ) {

            if( mSettings->mAmount >= currLen ) {
                mSettings->mAmount -= currLen;
            } else {
                mSettings->mAmount = 0;
            }
        }

    } while ( ! (sInterupted  ||
                   (!mMode_Time  &&  0 >= mSettings->mAmount)) && canRead );


    gettimeofday( &(reportstruct->packetTime), NULL );


    if(0.0 == mSettings->mInterval) {
        reportstruct->packetLen = totLen;
        ReportPacket( mSettings->reporthdr, reportstruct );
    }
    CloseReport( mSettings->reporthdr, reportstruct );

    DELETE_PTR( reportstruct );
    EndReport( mSettings->reporthdr );
}
