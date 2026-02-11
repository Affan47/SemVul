jpgEncode_setDefaultInputTraits (
    IP_XFORM_HANDLE  hXform,
    PIP_IMAGE_TRAITS pTraits)
{
    PJENC_INST g;

    HANDLE_TO_PTR (hXform, g);
    g->traits = *pTraits;

    INSURE (g->traits.iPixelsPerRow > 0);
    INSURE (g->traits.iComponentsPerPixel==1 || g->traits.iComponentsPerPixel==3);

    g->pixels_in_row  = g->traits.iPixelsPerRow;
    g->comps_in_pixel = g->traits.iComponentsPerPixel;
    g->rows_in_page   = g->traits.lNumRows;
    g->xRes           = g->traits.lHorizDPI >> 16;
    g->yRes           = g->traits.lVertDPI  >> 16;
    if (g->xRes < 0) g->xRes = 300;
    if (g->yRes < 0) g->yRes = 300;

    g->fDidHeader = FALSE;
    return IP_DONE;

    fatal_error:
        return IP_FATAL_ERROR;
}
