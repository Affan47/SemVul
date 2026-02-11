writeAppSegs( void )
{
    std::vector<ExifAppSegment*> appSegs = mAppSegManager->getAllAppSegs(false) ;

    int numOfAppSegs = appSegs.size() ;

    for ( int i = 0; i < numOfAppSegs; i++ )
        appSegs[i]->write( mExifio ) ;

    return EXIF_OK;
}
