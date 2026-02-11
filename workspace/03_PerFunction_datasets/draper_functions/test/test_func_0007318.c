SetOutputDataFormat(void)
{
	cmsIT8DefineDblFormat(hIT8out, "%.4g");
    cmsIT8SetPropertyStr(hIT8out, "ORIGINATOR", "icctrans");

    if (IncludePart != NULL)
        cmsIT8SetPropertyStr(hIT8out, ".INCLUDE", IncludePart);

    cmsIT8SetComment(hIT8out, "Data follows");
    cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_SETS", nMaxPatches);


    switch (OutputColorSpace) {


    case cmsSigXYZData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "XYZ_X");
        cmsIT8SetDataFormat(hIT8out, 2, "XYZ_Y");
        cmsIT8SetDataFormat(hIT8out, 3, "XYZ_Z");
        break;

    case cmsSigLabData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "LAB_L");
        cmsIT8SetDataFormat(hIT8out, 2, "LAB_A");
        cmsIT8SetDataFormat(hIT8out, 3, "LAB_B");
        break;


    case cmsSigRgbData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "RGB_R");
        cmsIT8SetDataFormat(hIT8out, 2, "RGB_G");
        cmsIT8SetDataFormat(hIT8out, 3, "RGB_B");
        break;

    case cmsSigGrayData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 2);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "GRAY");
        break;

    case cmsSigCmykData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 5);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "CMYK_C");
        cmsIT8SetDataFormat(hIT8out, 2, "CMYK_M");
        cmsIT8SetDataFormat(hIT8out, 3, "CMYK_Y");
        cmsIT8SetDataFormat(hIT8out, 4, "CMYK_K");
        break;

    case cmsSigCmyData:
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(hIT8out, 1, "CMY_C");
        cmsIT8SetDataFormat(hIT8out, 2, "CMY_M");
        cmsIT8SetDataFormat(hIT8out, 3, "CMY_Y");
        break;

    default: {

        int i, n;
        char Buffer[255];

        n = cmsChannelsOf(OutputColorSpace);
        cmsIT8SetPropertyDbl(hIT8out, "NUMBER_OF_FIELDS", n+1);
        cmsIT8SetDataFormat(hIT8out, 0, "SAMPLE_ID");

        for (i=1; i <= n; i++) {
            sprintf(Buffer, "CHAN_%d", i);
            cmsIT8SetDataFormat(hIT8out, i, Buffer);
        }
    }
    }
}
