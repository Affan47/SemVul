writeRationalArray( ExifIO* exifio, ExifDirEntry& dirEntry,
                                 exif_int32* dp )
{
    dirEntry.offset = exifio->seek( mDataOffset, SEEK_SET ) - mWriteOffset ;
    exifio->swabArrayOfLong((exif_uint32*)dp, 2*dirEntry.count);
    exifio->write(dp, 2*dirEntry.count*sizeof(exif_int32));
    mDataOffset = exifio->seek(0, SEEK_END);

    if ( ((mDataOffset-mWriteOffset)%2) == 1 )
        mDataOffset++;

    exifio->swabLong(&dirEntry.offset);
}
