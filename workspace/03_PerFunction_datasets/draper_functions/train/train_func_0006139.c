SelectHeader (PrintContext* pc)
{
    DRIVER_ERROR    err = NO_ERROR;
    DWORD           dwSize;
    int             iPlanes = 1;
    QUALITY_MODE        cqm;
    MEDIATYPE           cmt;
    BOOL                cdt;
    err = pc->GetPrintModeSettings (cqm, cmt, m_cmColorMode, cdt);

    if (m_cmColorMode == COLOR && m_bIamColor)
    {
        iPlanes = 4;
        m_iP[0] = 3;
    }
    m_dwWidth = pc->OutputPixelsPerRow () / 8;
    if (m_dwWidth % 8)
    {
        m_dwWidth = (m_dwWidth / 8 + 1) * 8;
    }
    m_dwLastRaster = (int) (pc->PrintableHeight () * pc->EffectiveResolutionY () + 0.5);
    dwSize = m_dwWidth * m_dwLastRaster * iPlanes * m_iBPP;
    m_pszInputRasterData = new BYTE[dwSize];
    if (m_pszInputRasterData == NULL)
    {
        return NULL;
    }
    m_pszCurPtr = m_pszInputRasterData;
    memset (m_pszCurPtr, 0, dwSize);
    thePrintContext = pc;
    return new HeaderLJZjs (this,pc);
}
