fetchLongArray( ExifIO* exifio, ExifDirEntry* dir )
{
    exif_int32* vec = new exif_int32[dir->count];

    if ( dir->count == 1 )
        vec[0] = dir->offset;
    else
    {
        fetchData( exifio, dir->offset, reinterpret_cast<int8*>(vec),
            dir->count*sizeof(exif_int32) );
        exifio->swabArrayOfLong( reinterpret_cast<exif_uint32*>(vec), dir->count);
    }

    return vec;
}
