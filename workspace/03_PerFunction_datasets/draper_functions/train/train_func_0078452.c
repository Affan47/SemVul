fakeMono_openXform (
    IP_XFORM_HANDLE *pXform)
{
    PFMON_INST g;

    INSURE (pXform != NULL);
    IP_MEM_ALLOC (sizeof(FMON_INST), g);
    *pXform = g;
    memset (g, 0, sizeof(FMON_INST));
    g->dwValidChk = CHECK_VALUE;
    g->iFakeDPI = 8;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
