ReadDateField(int nWidth)
{
    int nDay, nMonth, nYear, status;
    nDay = nMonth = nYear = 0;

    if ((status = ReadDateField(nWidth, &nYear, &nMonth, &nDay)) == -1)
       return "";

    sprintf(m_szBuffer, "%4.4d%2.2d%2.2d", nYear, nMonth, nDay);

    return m_szBuffer;
}
