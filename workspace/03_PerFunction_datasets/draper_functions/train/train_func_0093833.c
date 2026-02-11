jpgFix_setDefaultInputTraits (
    IP_XFORM_HANDLE  hXform,
    PIP_IMAGE_TRAITS pTraits)
{
    PJFIX_INST g;

    HANDLE_TO_PTR (hXform, g);

    return jpgDecodeTbl.setDefaultInputTraits(g->pSlaveXform,pTraits);

    fatal_error:
    return IP_FATAL_ERROR;
}
