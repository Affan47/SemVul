Seek( vsi_l_offset nOffset, int nWhence )
{
    if (nWhence == SEEK_SET)
    {
        curOffset = nOffset;
    }
    else if (nWhence == SEEK_CUR)
    {
        curOffset = curOffset + nOffset;
    }
    else
    {
        curOffset = GetFileSize() + nOffset;
    }
    bEOF = FALSE;
    return 0;
}
