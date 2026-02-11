GetNoDataValue( int *pbSuccess )
{
    CPLErr eErr = LoadData();
    if (eErr != CE_None ||
        m_Grib_MetaData == NULL ||
        m_Grib_MetaData->gridAttrib.f_miss == 0)
    {
        if (pbSuccess)
            *pbSuccess = FALSE;
        return 0;
    }

    if (m_Grib_MetaData->gridAttrib.f_miss == 2)
    {

        CPLDebug("GRIB", "Secondary missing value also set for band %d : %f",
                 nBand, m_Grib_MetaData->gridAttrib.missSec);
    }

    if (pbSuccess)
        *pbSuccess = TRUE;
    return m_Grib_MetaData->gridAttrib.missPri;
}
