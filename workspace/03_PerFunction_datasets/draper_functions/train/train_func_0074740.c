open( const char* filename, const char* cmode)
{
    ExifStatus status = EXIF_FILE_OPEN_ERROR ;

    mIOwnExifIO = true ;
    mExifio = ExifIO::open( status, filename, cmode ) ;

    if( mExifio )
    {
        mFileName = filename ;
        status = initAfterOpen( cmode ) ;
    }

    return status ;
}
