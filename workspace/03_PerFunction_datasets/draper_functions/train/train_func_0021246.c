IsBlockAvailable( int nBlockId )

{
    toff_t *panByteCounts = NULL;

    if( ( TIFFIsTiled( hTIFF )
          && TIFFGetField( hTIFF, TIFFTAG_TILEBYTECOUNTS, &panByteCounts ) )
        || ( !TIFFIsTiled( hTIFF )
          && TIFFGetField( hTIFF, TIFFTAG_STRIPBYTECOUNTS, &panByteCounts ) ) )
    {
        if( panByteCounts == NULL )
            return FALSE;
        else
            return panByteCounts[nBlockId] != 0;
    }
    else
        return FALSE;
}
