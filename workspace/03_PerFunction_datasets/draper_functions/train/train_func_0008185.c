SendWhiteStrips (int iPageHeight, BOOL bGray)
{
    DRIVER_ERROR    err = NO_ERROR;
	HPLJBITMAP      hWhiteBitmap;
    QTABLEINFO      qTableInfo;
    RASTERDATA      whiteRaster;

    qTableInfo.qFactor = 6;

	hWhiteBitmap.pvBits = NULL;

	if (bGray)
	{
        m_SourceBitmap.cjBits = m_iRasterWidth * MOJAVE_STRIP_HEIGHT;
        memset (m_SourceBitmap.pvBits, 0x00, m_SourceBitmap.cjBits);
    }
    else
    {
        m_SourceBitmap.cjBits = m_iRasterWidth * MOJAVE_STRIP_HEIGHT * 3;
        memset (m_SourceBitmap.pvBits, 0xFF, m_SourceBitmap.cjBits);
    }
	memset(&m_SourceBitmap.bitmapInfo.bmiHeader, 0, sizeof(HPBITMAPINFOHEADER));
	m_SourceBitmap.bitmapInfo.bmiHeader.biWidth = m_iRasterWidth;
	m_SourceBitmap.bitmapInfo.bmiHeader.biHeight = MOJAVE_STRIP_HEIGHT;
	m_SourceBitmap.bitmapInfo.bmiHeader.biSizeImage = m_SourceBitmap.cjBits;
	m_SourceBitmap.bitmapInfo.bmiHeader.biBitCount = 8;
    Compress (&m_SourceBitmap, &m_DestBitmap, &qTableInfo, bGray);
    whiteRaster.rastersize[COLORTYPE_COLOR] = m_DestBitmap.cjBits;
    whiteRaster.rasterdata[COLORTYPE_COLOR] = m_DestBitmap.pvBits;
    while (m_lPrinterRasterRow < iPageHeight)
    {
        thePrinter->Encapsulate (&whiteRaster, TRUE);
        m_lPrinterRasterRow += MOJAVE_STRIP_HEIGHT;
    }

    return err;
}
