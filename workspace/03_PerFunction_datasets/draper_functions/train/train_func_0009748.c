PutCGATSValues(cmsFloat64Number Float[])
{
    cmsIT8SetData(hIT8out, CGATSPatch, "SAMPLE_ID", CGATSPatch);
    switch (OutputColorSpace) {


    case cmsSigXYZData:

        SetCGATSfld("XYZ_X", Float[0] * 100.0);
        SetCGATSfld("XYZ_Y", Float[1] * 100.0);
        SetCGATSfld("XYZ_Z", Float[2] * 100.0);
        break;

    case cmsSigLabData:

        SetCGATSfld("LAB_L", Float[0]);
        SetCGATSfld("LAB_A", Float[1]);
        SetCGATSfld("LAB_B", Float[2]);
        break;


    case cmsSigRgbData:
        SetCGATSfld("RGB_R", Float[0] * 255.0);
        SetCGATSfld("RGB_G", Float[1] * 255.0);
        SetCGATSfld("RGB_B", Float[2] * 255.0);
        break;

    case cmsSigGrayData:
        SetCGATSfld("GRAY", Float[0] * 255.0);
        break;

    case cmsSigCmykData:
        SetCGATSfld("CMYK_C", Float[0]);
        SetCGATSfld("CMYK_M", Float[1]);
        SetCGATSfld("CMYK_Y", Float[2]);
        SetCGATSfld("CMYK_K", Float[3]);
        break;

    case cmsSigCmyData:
        SetCGATSfld("CMY_C", Float[0]);
        SetCGATSfld("CMY_M", Float[1]);
        SetCGATSfld("CMY_Y", Float[2]);
        break;

    default:
        {

            cmsUInt32Number i, n;

            n = cmsChannelsOf(InputColorSpace);
            for (i=0; i < n; i++) {

                char Buffer[255];

                sprintf(Buffer, "CHAN_%d", i+1);

                SetCGATSfld(Buffer, Float[i]);
            }
        }
    }
}
