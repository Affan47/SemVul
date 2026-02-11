setColorMap(ExifJpegColorMap *colorMap,
                                      bool applyToData)
{

    if(colorMap == NULL)
    {
        return EXIF_ERROR;
    }
    if(colorMap->colorMap0 == NULL || colorMap->colorMap1 == NULL ||
       colorMap->colorMap2 == NULL)
    {
        return EXIF_ERROR;
    }
    if(mJpegColorMap)
    {
        delete mJpegColorMap;
        mJpegColorMap = NULL;
    }

    mJpegColorMap = new ExifJpegColorMap;
    mJpegColorMap->colorMap0 = new uint16[colorMap->numColors];
    mJpegColorMap->colorMap1 = new uint16[colorMap->numColors];
    mJpegColorMap->colorMap2 = new uint16[colorMap->numColors];

    memcpy(mJpegColorMap->colorMap0, colorMap->colorMap0,
        colorMap->numColors * sizeof(uint16));
    memcpy(mJpegColorMap->colorMap1, colorMap->colorMap1,
        colorMap->numColors * sizeof(uint16));
    memcpy(mJpegColorMap->colorMap1, colorMap->colorMap1,
        colorMap->numColors * sizeof(uint16));
    mUseColorMap = true;
    mApplyColorMap = applyToData;

    return EXIF_OK ;
}
