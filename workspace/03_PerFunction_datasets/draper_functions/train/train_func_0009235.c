appendToStrip(exif_uint32 strip, tdata_t data,
                                         tsize_t cc)
{
    std::vector<exif_uint32> offset = mExifdir->stripOffsets();
    std::vector<exif_uint32> bytecount = mExifdir->stripByteCounts();

    exif_int32 stripPtr = offset[strip] + bytecount[strip] ;


    if (offset[strip] != 0) {
        if (mExifio->seek(stripPtr, SEEK_SET )!= stripPtr )
        {

            return EXIF_ERROR;
        }
    }
    else
        offset[strip] = mExifio->seek((exifoff_t) 0, SEEK_END) ;


    if (mExifio->write(data, cc) != cc)
    {

        return EXIF_ERROR;

    }

    bytecount[strip] += cc;

    ExifTagEntry* off = mExifdir->getGenericTag( EXIFTAG_STRIPOFFSETS );
    ExifTagEntry* cnt = mExifdir->getGenericTag( EXIFTAG_STRIPBYTECOUNTS );
    if( off->getCount() > 1 )
    {
        ExifTagEntryT< std::vector<exif_uint32> >* temp =
            (ExifTagEntryT< std::vector<exif_uint32> >*)off;
        temp->setValue(offset);
    }
    else
    {
        ExifTagEntryT<exif_uint32>* temp = (ExifTagEntryT<exif_uint32>*)off;
        temp->setValue(offset.front()) ;
    }
    if( cnt->getCount() > 1 )
    {
        ExifTagEntryT< std::vector<exif_uint32> >* temp =
            (ExifTagEntryT< std::vector<exif_uint32> >*)cnt;
        temp->setValue(bytecount);
    }
    else
    {
        ExifTagEntryT<exif_uint32>* temp = (ExifTagEntryT<exif_uint32>*)cnt;
        temp->setValue(bytecount.front()) ;
    }

    return EXIF_OK;
}
