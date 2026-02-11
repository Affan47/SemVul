read( ExifIO* exifio )
{
    ExifStatus status = EXIF_OK;
    mRawData = new char[mLength];
    if ( mRawData )
    {
        if( exifio->read( mRawData, mLength ) != mLength)
            status = EXIF_FILE_READ_ERROR ;
    }
    else
        status = EXIF_ERROR ;

    return status ;
}
