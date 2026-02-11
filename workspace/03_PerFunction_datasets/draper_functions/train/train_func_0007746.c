getAllTiffAppSegs()
{
    std::vector<ExifAppSegment*> appSegs ;

    if ( mChild )
    {

        mChild->getThisAppSeg() ;

        if ( mChild->mAppSeg->isTiff() )
            appSegs.push_back( mChild->mAppSeg ) ;

        mChild->getAllTiffAppSegs( appSegs ) ;
    }

    return appSegs ;
}
