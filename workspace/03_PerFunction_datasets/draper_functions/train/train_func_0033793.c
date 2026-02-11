ReceivedBytes(GByte *buffer, size_t count, size_t nmemb)
{
    size_t nSize = count * nmemb;
    nBodySize += nSize;

    if (ENABLE_DEBUG)
        CPLDebug("VSICURL", "Receiving %d bytes...", (int)nSize);

    if( bHasCandidateFileSize && bCanTrustCandidateFileSize && !bHastComputedFileSize )
    {
        poFS->AcquireMutex();
        CachedFileProp* cachedFileProp = poFS->GetCachedFileProp(pszURL);
        cachedFileProp->fileSize = fileSize = nCandidateFileSize;
        cachedFileProp->bHastComputedFileSize = bHastComputedFileSize = TRUE;
        if (ENABLE_DEBUG)
            CPLDebug("VSICURL", "File size = " CPL_FRMT_GUIB, fileSize);
        poFS->ReleaseMutex();
    }

    AcquireMutex();
    if (eExists == EXIST_UNKNOWN)
    {
        poFS->AcquireMutex();
        CachedFileProp* cachedFileProp = poFS->GetCachedFileProp(pszURL);
        cachedFileProp->eExists = eExists = EXIST_YES;
        poFS->ReleaseMutex();
    }
    else if (eExists == EXIST_NO)
    {
        ReleaseMutex();
        return 0;
    }

    while(TRUE)
    {
        size_t nFree = oRingBuffer.GetCapacity() - oRingBuffer.GetSize();
        if (nSize <= nFree)
        {
            oRingBuffer.Write(buffer, nSize);


            CPLCondSignal(hCondProducer);

            if (bAskDownloadEnd)
            {
                if (ENABLE_DEBUG)
                    CPLDebug("VSICURL", "Download interruption asked");

                ReleaseMutex();
                return 0;
            }
            break;
        }
        else
        {
            oRingBuffer.Write(buffer, nFree);
            buffer += nFree;
            nSize -= nFree;


            CPLCondSignal(hCondProducer);

            if (ENABLE_DEBUG)
                CPLDebug("VSICURL", "Waiting for reader to consume some bytes...");

            while(oRingBuffer.GetSize() == oRingBuffer.GetCapacity() && !bAskDownloadEnd)
            {
                CPLCondWait(hCondConsumer, hRingBufferMutex);
            }

            if (bAskDownloadEnd)
            {
                if (ENABLE_DEBUG)
                    CPLDebug("VSICURL", "Download interruption asked");

                ReleaseMutex();
                return 0;
            }
        }
    }

    ReleaseMutex();

    return nmemb;
}
