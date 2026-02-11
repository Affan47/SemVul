OGRGetXMLDateTime(int year, int month, int day, int hour, int minute, int second, int TZFlag)
{
    char* pszRet;
    if (TZFlag == 0 || TZFlag == 100)
    {
        pszRet = CPLStrdup(CPLSPrintf("%04d-%02d-%02dT%02d:%02d:%02dZ",
                           year, month, day, hour, minute, second));
    }
    else
    {
        int TZOffset = ABS(TZFlag - 100) * 15;
        int TZHour = TZOffset / 60;
        int TZMinute = TZOffset - TZHour * 60;
        pszRet = CPLStrdup(CPLSPrintf("%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d",
                           year, month, day, hour, minute, second,
                           (TZFlag > 100) ? '+' : '-', TZHour, TZMinute));
    }
    return pszRet;
}
