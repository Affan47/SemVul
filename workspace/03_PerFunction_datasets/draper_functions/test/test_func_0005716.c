skel_setXformSpec (
    IP_XFORM_HANDLE hXform,
    DWORD_OR_PVOID  aXformInfo[])
{
    PSKEL_INST g;

    HANDLE_TO_PTR (hXform, g);


    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
