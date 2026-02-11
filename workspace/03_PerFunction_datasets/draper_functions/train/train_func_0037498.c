fakeMono_closeXform (IP_XFORM_HANDLE hXform)
{
    PFMON_INST g;

    HANDLE_TO_PTR (hXform, g);

    g->dwValidChk = 0;
    IP_MEM_FREE (g);

    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
