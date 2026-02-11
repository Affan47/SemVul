Read( void *pBuffer, size_t nSize, size_t nMemb )
{
    const size_t nTotalToRead = nSize * nMemb;


    if (nSize == 0)
        return 0;

    if (nBufferSize != 0 &&
        nCurOffset >= nBufferOffset && nCurOffset <= nBufferOffset + nBufferSize)
    {

        const int nReadInBuffer = (int) MIN(nTotalToRead, nBufferOffset + nBufferSize - nCurOffset);
        memcpy(pBuffer, pabyBuffer + nCurOffset - nBufferOffset, nReadInBuffer);
        const int nToReadInFile = nTotalToRead - nReadInBuffer;
        if (nToReadInFile > 0)
        {


            if (bNeedBaseHandleSeek)
                poBaseHandle->Seek(nBufferOffset + nBufferSize, SEEK_SET);
            bNeedBaseHandleSeek = FALSE;


            const int nReadInFile = poBaseHandle->Read((GByte*)pBuffer + nReadInBuffer, 1, nToReadInFile);
            const int nRead = nReadInBuffer + nReadInFile;

            nBufferSize = MIN(nRead, MAX_BUFFER_SIZE);
            nBufferOffset = nCurOffset + nRead - nBufferSize;
            memcpy(pabyBuffer, (GByte*)pBuffer + nRead - nBufferSize, nBufferSize);

            nCurOffset += nRead;


            bEOF = poBaseHandle->Eof();

            return nRead / nSize;
        }
        else
        {

            nCurOffset += nTotalToRead;
            return nTotalToRead / nSize;
        }
    }
    else
    {

        poBaseHandle->Seek(nCurOffset, SEEK_SET);
        bNeedBaseHandleSeek = FALSE;
        const int nReadInFile = poBaseHandle->Read(pBuffer, 1, nTotalToRead);
        nBufferSize = MIN(nReadInFile, MAX_BUFFER_SIZE);
        nBufferOffset = nCurOffset + nReadInFile - nBufferSize;
        memcpy(pabyBuffer, (GByte*)pBuffer + nReadInFile - nBufferSize, nBufferSize);

        nCurOffset += nReadInFile;


        bEOF = poBaseHandle->Eof();

        return nReadInFile / nSize;
    }

}
