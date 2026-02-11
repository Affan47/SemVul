Write( const void * pBuffer, size_t nSize, size_t nCount )

{
    bAtEOF = FALSE;

    if (nSubregionSize == 0)
        return VSIFWriteL( pBuffer, nSize, nCount, fp );

    if (nSize == 0)
        return 0;

    vsi_l_offset nCurOffset = VSIFTellL(fp);
    if (nCurOffset >= nSubregionOffset + nSubregionSize)
        return 0;

    size_t nByteToWrite = nSize * nCount;
    if (nCurOffset + nByteToWrite > nSubregionOffset + nSubregionSize)
    {
        int nWritten = (int)VSIFWriteL( pBuffer, 1, (size_t)(nSubregionOffset + nSubregionSize - nCurOffset), fp);
        return nWritten / nSize;
    }
    else
        return VSIFWriteL( pBuffer, nSize, nCount, fp );
}
