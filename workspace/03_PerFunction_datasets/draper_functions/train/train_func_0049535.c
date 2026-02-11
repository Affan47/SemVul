remove( uint16 marker, const char * ID )
{
    ExifStatus status = EXIF_OK ;

    if ( mChild )
    {
        if ( mChild->mAppSeg->getAppSegmentMarker() == marker &&
            strcmp(mChild->mAppSeg->getAppIdent(),ID) == 0 )
        {
            ExifAppSegManager* grandChild = mChild->mChild ;


            mChild->mChild = NULL ;
            delete mChild ;


            mChild = grandChild ;
        }
        else
            status = mChild->remove( marker, ID ) ;
    }
    else
        status = EXIF_ERROR ;

    return status ;
}
