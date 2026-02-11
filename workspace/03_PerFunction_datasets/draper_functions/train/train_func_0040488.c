ReadAvhrrScanlineRecord(int nPos,
                                           AvhrrLine_t *psScanlineRecord)
{
    int i;
    AvhrrLine_t *sr = psScanlineRecord;

    sr->nScanLineNum = ReadAvhrrInt32((unsigned char*)seg_data.Get(nPos,4));
    sr->nStartScanTimeGMTMsec = ReadAvhrrInt32((unsigned char*)seg_data.Get(nPos+4,4));

    for(i = 0; i < 10; ++i)
        sr->abyScanLineQuality[i] = seg_data.GetInt(nPos+8+i,1);

    for(i = 0; i < 5; ++i)
    {
        sr->aabyBadBandIndicators[i][0] = seg_data.GetInt(nPos+18+2*i,1);
        sr->aabyBadBandIndicators[i][1] = seg_data.GetInt(nPos+18+2*i+1,1);
    }

    for(i = 0; i < 8; ++i)
        sr->abySatelliteTimeCode[i] = seg_data.GetInt(nPos+28+i,1);

    for(i = 0; i < 3; ++i)
        sr->anTargetTempData[i] = ReadAvhrrInt32((unsigned char*)seg_data.Get(nPos+36+i*4,4));
    for(i = 0; i < 3; ++i)
        sr->anTargetScanData[i] = ReadAvhrrInt32((unsigned char*)seg_data.Get(nPos+48+i*4,4));
    for(i = 0; i < 5; ++i)
        sr->anSpaceScanData[i]  = ReadAvhrrInt32((unsigned char*)seg_data.Get(nPos+60+i*4,4));
}
