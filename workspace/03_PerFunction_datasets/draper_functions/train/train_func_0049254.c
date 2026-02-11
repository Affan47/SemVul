initAfterOpen( const char* cmode )
{


    mExifio->flags() |= FILLORDER_MSB2LSB ;


    const char* cp ;
    for(cp = cmode; *cp; cp++)
    {
        switch (*cp)
        {
            case 'B':
                mExifio->flags() = (mExifio->flags() &~ EXIF_FILLORDER) |
                    FILLORDER_MSB2LSB;
                break;
            case 'L':
                mExifio->flags() = (mExifio->flags() &~ EXIF_FILLORDER) |
                    FILLORDER_LSB2MSB;
                break;
            case 'H':
                mExifio->flags() = (mExifio->flags() &~ EXIF_FILLORDER) |
                    HOST_FILLORDER;
                break;
        }
    }

    mAppSegManager->clear() ;


    bool bigendian = HOST_BIGENDIAN ;
    initEndian( bigendian );
    ExifStatus status ;


    if( mExifio->mode() & O_CREAT )
    {
        status = initAppSegs( mExifio ) ;

    }
    else if( (mExifio->mode() & O_RDWR) && (ExifImageFile::isExifFile(mExifio)
        != EXIF_OK) && (ExifJpegImage::isJpegFile( mExifio ) == EXIF_OK) )
    {


        char buf[20];
        ExifIO * tmpExifIO = new ExifIO(status,buf,20, "w");
        if( status == EXIF_OK )
        {
            tmpExifIO->flags() = mExifio->flags();
            status = initAppSegs( tmpExifIO );
            tmpExifIO->close();
            delete tmpExifIO;
            if( status == EXIF_OK )
            {
                status = ExifJpegImage::initAfterOpen( cmode ) ;


                if ( status == EXIF_OK )
                {


                    ExifImageInfo imgInfo ;
                    if ( getImageInfo( imgInfo ) == EXIF_OK )
                    {
                        ExifTagEntry * tagEntry = new ExifTagEntryT<exif_uint32>
                            ( EXIFTAG_PIXELXDIMENSION, EXIF_LONG, 1,
                              imgInfo.width );
                        setGenericTag(*tagEntry,EXIF_APP1_EXIFIFD);
                        delete tagEntry ;
                        tagEntry = new ExifTagEntryT<exif_uint32>
                            ( EXIFTAG_PIXELYDIMENSION, EXIF_LONG, 1,
                              imgInfo.height );
                        setGenericTag(*tagEntry,EXIF_APP1_EXIFIFD);
                        delete tagEntry ;
                    }
                }
            }
        }

    }
    else
    {


        status = readImage();
    }

    return status;
}
