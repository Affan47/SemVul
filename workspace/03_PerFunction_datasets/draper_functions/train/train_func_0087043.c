DetectFileKeyByContent(void * pvFileContent, DWORD dwFileSize)
{
    DWORD dwFileKey;


    if(dwFileSize >= 0x0C)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 3, 0x46464952, dwFileSize - 8, 0x45564157);
        if(dwFileKey != 0)
            return dwFileKey;
    }


    if(dwFileSize > 0x40)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 2, 0x00905A4D, 0x00000003);
        if(dwFileKey != 0)
            return dwFileKey;
    }


    if(dwFileSize > 0x04)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 2, 0x6D783F3C, 0x6576206C);
        if(dwFileKey != 0)
            return dwFileKey;
    }


    return 0;
}
