postWallClockTime (EventCapsetID capset)
{
    StgWord64 ts;
    StgWord64 sec;
    StgWord32 nsec;

    ACQUIRE_LOCK(&eventBufMutex);


    getUnixEpochTime(&sec, &nsec);
    ts = time_ns();

    if (!hasRoomForEvent(&eventBuf, EVENT_WALL_CLOCK_TIME)) {

        printAndClearEventBuf(&eventBuf);
    }


    postEventTypeNum(&eventBuf, EVENT_WALL_CLOCK_TIME);
    postWord64(&eventBuf, ts);


    postCapsetID(&eventBuf, capset);
    postWord64(&eventBuf, sec);
    postWord32(&eventBuf, nsec);

    RELEASE_LOCK(&eventBufMutex);
}
