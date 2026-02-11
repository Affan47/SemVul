jpgFix_openXform (
    IP_XFORM_HANDLE *pXform)
{
    PJFIX_INST g;

    INSURE (pXform != NULL);
    IP_MEM_ALLOC (sizeof(JFIX_INST), g);
    *pXform = g;
    memset (g, 0, sizeof(JFIX_INST));
    if (jpgDecodeTbl.openXform(&g->pSlaveXform)!=IP_DONE) {
        IP_MEM_FREE(g);
        goto fatal_error;
    }
    g->dwValidChk = CHECK_VALUE;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
