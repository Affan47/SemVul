SanityCheckOK(GDALDataset* sourceDS)
{
    int src_nBlockXSize, src_nBlockYSize;
    int nBlockXSize, nBlockYSize;
    double adfGeoTransform[6];
    if (checkDone)
        return checkOK;

    checkOK = TRUE;
    checkDone = TRUE;

    sourceDS->GetGeoTransform(adfGeoTransform);
    WARN_ON_FAIL(fabs(adfGeoTransform[GEOTRSFRM_TOPLEFT_X] - nwLong) < adfGeoTransform[1] );
    WARN_ON_FAIL(fabs(adfGeoTransform[GEOTRSFRM_TOPLEFT_Y] - nwLat) < fabs(adfGeoTransform[5]) );
    WARN_ON_FAIL(adfGeoTransform[GEOTRSFRM_ROTATION_PARAM1] == 0 &&
                  adfGeoTransform[GEOTRSFRM_ROTATION_PARAM2] == 0);
    ERROR_ON_FAIL(sourceDS->GetRasterCount() == 1);
    ERROR_ON_FAIL(sourceDS->GetRasterXSize() == nRasterXSize);
    ERROR_ON_FAIL(sourceDS->GetRasterYSize() == nRasterYSize);
    WARN_ON_FAIL(EQUAL(sourceDS->GetProjectionRef(), GetProjectionRef()));
    sourceDS->GetRasterBand(1)->GetBlockSize(&src_nBlockXSize, &src_nBlockYSize);
    GetRasterBand(1)->GetBlockSize(&nBlockXSize, &nBlockYSize);
    ERROR_ON_FAIL(src_nBlockXSize == nBlockXSize);
    ERROR_ON_FAIL(src_nBlockYSize == nBlockYSize);
    WARN_ON_FAIL(sourceDS->GetRasterBand(1)->GetColorInterpretation() == GCI_PaletteIndex);
    WARN_ON_FAIL(sourceDS->GetRasterBand(1)->GetRasterDataType() == GDT_Byte);

    return checkOK;
}
