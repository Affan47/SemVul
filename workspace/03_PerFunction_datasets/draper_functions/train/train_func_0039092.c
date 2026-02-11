WriteGENFile()
{
    if (!bGeoTransformValid)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "No geo transform available !");
        adfGeoTransform[0] = 0;
        adfGeoTransform[3] = 0;
        adfGeoTransform[1] = 1;
        adfGeoTransform[5] = 1;
    }

    LSO = adfGeoTransform[0];
    PSO = adfGeoTransform[3];
    ARV = (int)floor(360. / adfGeoTransform[1] + .5);
    BRV = (int)floor(-360. / adfGeoTransform[5] + .5);


    int SCA = (int)floor(1000000. * 400384 / BRV + 0.5);

    int nOvSizeX = nRasterXSize;
    int nOvSizeY = nRasterYSize;


    WriteGENFile_Header(fdGEN);


    WriteGENFile_DataSetDescriptionRecord(fdGEN);


    WriteGENFile_OverviewRecord(fdGEN, osBaseFileName, ARV, BRV, LSO, PSO,
                                nOvSizeX, nOvSizeY, NFL, NFC, TILEINDEX);


    CPLString osNAM = osBaseFileName;
    char tmp[12+1];
    sprintf(tmp, "%s.IMG", osNAM.c_str());
    CPLString osBAD = tmp;
    WriteGENFile_GeneralInformationRecord(fdGEN, osNAM, osBAD, ARV, BRV, LSO, PSO,
                                          adfGeoTransform, SCA, nRasterXSize, nRasterYSize, NFL, NFC, TILEINDEX);

    if (CSLTestBoolean(CPLGetConfigOption("ADRG_SIMULATE_MULTI_IMG", "OFF")))
    {
        strncpy(tmp, osBaseFileName.c_str(), 6);
        tmp[6] = '\0';
        strcat(tmp, "02");
        osNAM = tmp;
        sprintf(tmp, "%s.IMG", osNAM.c_str());
        osBAD = tmp;
        WriteGENFile_GeneralInformationRecord(fdGEN, osNAM, osBAD, ARV, BRV, LSO, PSO,
                                              adfGeoTransform, SCA, nRasterXSize, nRasterYSize, NFL, NFC, TILEINDEX);
    }
}
