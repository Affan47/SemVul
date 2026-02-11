DownloadInThread()
{
    VSICurlSetOptions(hCurlHandle, pszURL);

    static int bHasCheckVersion = FALSE;
    static int bSupportGZip = FALSE;
    if (!bHasCheckVersion)
    {
        bSupportGZip = strstr(curl_version(), "zlib/") != NULL;
        bHasCheckVersion = TRUE;
    }
    if (bSupportGZip && CSLTestBoolean(CPLGetConfigOption("CPL_CURL_GZIP", "YES")))
    {
        curl_easy_setopt(hCurlHandle, CURLOPT_ENCODING, "gzip");
    }

    if (pabyHeaderData == NULL)
        pabyHeaderData = (GByte*) CPLMalloc(HEADER_SIZE + 1);
    nHeaderSize = 0;
    nBodySize = 0;
    nHTTPCode = 0;

    curl_easy_setopt(hCurlHandle, CURLOPT_HEADERDATA, this);
    curl_easy_setopt(hCurlHandle, CURLOPT_HEADERFUNCTION, VSICurlStreamingHandleReceivedBytesHeader);

    curl_easy_setopt(hCurlHandle, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(hCurlHandle, CURLOPT_WRITEFUNCTION, VSICurlStreamingHandleReceivedBytes);

    char szCurlErrBuf[CURL_ERROR_SIZE+1];
    szCurlErrBuf[0] = '\0';
    curl_easy_setopt(hCurlHandle, CURLOPT_ERRORBUFFER, szCurlErrBuf );

    CURLcode eRet = curl_easy_perform(hCurlHandle);

    curl_easy_setopt(hCurlHandle, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(hCurlHandle, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(hCurlHandle, CURLOPT_HEADERDATA, NULL);
    curl_easy_setopt(hCurlHandle, CURLOPT_HEADERFUNCTION, NULL);

    AcquireMutex();
    if (!bAskDownloadEnd && eRet == 0 && !bHastComputedFileSize)
    {
        poFS->AcquireMutex();
        CachedFileProp* cachedFileProp = poFS->GetCachedFileProp(pszURL);
        cachedFileProp->fileSize = fileSize = nBodySize;
        cachedFileProp->bHastComputedFileSize = bHastComputedFileSize = TRUE;
        if (ENABLE_DEBUG)
            CPLDebug("VSICURL", "File size = " CPL_FRMT_GUIB, fileSize);
        poFS->ReleaseMutex();
    }

    bDownloadInProgress = FALSE;
    bDownloadStopped = TRUE;


    CPLCondSignal(hCondProducer);
    ReleaseMutex();
}
