JbigCompress ()
{
    DRIVER_ERROR        err = NO_ERROR;
    HPLJZjcBuff         myBuffer;
    int                 iPlanes = (m_cmColorMode == COLOR) ? 4 : 1;
    int                 iIncr = (m_bIamColor) ? 100 : m_dwLastRaster;

    HPLJZjsJbgEncSt   se;
    BYTE    *bitmaps[4] =
            {
                m_pszInputRasterData,
                m_pszInputRasterData + (m_dwWidth * m_iBPP * m_dwLastRaster),
                m_pszInputRasterData + (m_dwWidth * m_iBPP * m_dwLastRaster * 2),
                m_pszInputRasterData + (m_dwWidth * m_iBPP * m_dwLastRaster * 3)
            };
    myBuffer.pszCompressedData = new BYTE[m_dwWidth * m_dwLastRaster * m_iBPP];
    myBuffer.dwTotalSize = 0;

    BYTE    *p;
    int      iHeight;
    for (DWORD y = 0; y < m_dwLastRaster; y += iIncr)
    {
        for (int i = 0; i < iPlanes; i++)
        {
            memset (myBuffer.pszCompressedData, 0, m_dwWidth * m_dwLastRaster * m_iBPP);
            myBuffer.dwTotalSize = 0;
            p = bitmaps[i] + (y * m_dwWidth * m_iBPP);
            iHeight = iIncr;
            if (y + iIncr > m_dwLastRaster)
            {
                iHeight = m_dwLastRaster - y;
            }

            HPLJJBGCompress (m_dwWidth * 8 * m_iBPP, iHeight, &p, &myBuffer, &se);

            if (i == 0)
            {
                StartPage (se.xd, se.yd);
            }
            err = this->SendPlaneData (i + 1, &se, &myBuffer, (y + iIncr) >= m_dwLastRaster);
        }
    }

    delete [] myBuffer.pszCompressedData;
    m_dwCurrentRaster = 0;
    m_pszCurPtr = m_pszInputRasterData;
    memset (m_pszCurPtr, 0, (m_dwWidth * m_dwLastRaster * iPlanes * m_iBPP));

    err = EndPage ();

    return err;
}
