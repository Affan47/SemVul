getRawAppSeg( uint16 marker,
    const char * ID, bool tryToConvert )
{
    ExifAppSegment* appSeg = NULL ;

    if ( mChild )
    {
        if ( mChild->mAppSeg->getAppSegmentMarker() == marker &&
            strcmp(mChild->mAppSeg->getAppIdent(),ID) == 0 )
        {
            if ( tryToConvert )
                appSeg = mChild->getThisAppSeg() ;
            else
                appSeg = mChild->mAppSeg ;


            if ( !appSeg->isRaw() )
                appSeg = mChild->getRawAppSeg( marker, ID, tryToConvert ) ;
        }
        else
            appSeg = mChild->getRawAppSeg( marker, ID, tryToConvert ) ;
    }

    return appSeg ;
}
