QueryColorSpaceWrapper( opvp_dc_t printerContext, opvp_int_t *pnum,
    opvp_cspace_t *pcspace)
{
    int r;
    int i;

    if ((r = apiEntry_0_2->QueryColorSpace(printerContext,
         (OPVP_ColorSpace *)pcspace,pnum)) != OPVP_OK) {

        return r;
    }

    for (i = 0;i < *pnum;i++) {
        if (pcspace[i]
             >= sizeof(cspace_0_2_to_1_0)/sizeof(opvp_cspace_t)) {


            pcspace[i] = OPVP_CSPACE_DEVICERGB;
        } else {
            pcspace[i] = cspace_0_2_to_1_0[pcspace[i]];
        }
    }
    return OPVP_OK;
}
