Seek( vsi_l_offset nOffset, int nWhence )

{
    bAtEOF = FALSE;

    if( nWhence == SEEK_SET )
        nOffset += nSubregionOffset;
    else if( nWhence == SEEK_CUR )
    {

    }
    else if( nWhence == SEEK_END )
    {
        if( nSubregionSize != 0 )
        {
            nOffset = nSubregionOffset + nSubregionSize;
            nWhence = SEEK_SET;
        }
    }
    else
    {
        errno = EINVAL;
        return -1;
    }

    return VSIFSeekL( fp, nOffset, nWhence );
}
