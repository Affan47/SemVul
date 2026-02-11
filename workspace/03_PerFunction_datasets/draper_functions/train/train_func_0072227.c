SetColorSpaceWrapper(opvp_dc_t printerContext, opvp_cspace_t cspace)
{
    if (cspace == OPVP_CSPACE_DEVICEKRGB) {

        *ErrorNo = OPVP_NOTSUPPORTED_0_2;
        return -1;
    }
    if (cspace
         >= sizeof(cspace_1_0_to_0_2)/sizeof(OPVP_ColorSpace)) {

        *ErrorNo = OPVP_PARAMERROR_0_2;
        return -1;
    }
    return  apiEntry_0_2->SetColorSpace(printerContext,
      cspace_1_0_to_0_2[cspace]);
}
