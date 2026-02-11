getAllRawAppSegs( uint16 marker, const char * ID,
    bool tryToConvert,
    std::vector<ExifAppSegment*>& vec  )
{
    if ( mChild )
    {
        if ( mChild->mAppSeg->getAppSegmentMarker() == marker &&
            strcmp(mChild->mAppSeg->getAppIdent(),ID) == 0 )
        {
            if ( tryToConvert )
                mChild->getThisAppSeg() ;

            if ( mChild->mAppSeg->isRaw() )
                vec.push_back( mChild->mAppSeg ) ;
        }

        mChild->getAllRawAppSegs( marker, ID, tryToConvert, vec ) ;
    }
}
