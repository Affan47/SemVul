rotate_setDefaultInputTraits (
    IP_XFORM_HANDLE  hXform,
    PIP_IMAGE_TRAITS pTraits)
{
    PROTATE_INST g;

    HANDLE_TO_PTR (hXform, g);


    INSURE (pTraits->iPixelsPerRow > 0  &&
            pTraits->lNumRows > 0  &&
            pTraits->iBitsPerPixel > 0);
    g->inTraits = *pTraits;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
