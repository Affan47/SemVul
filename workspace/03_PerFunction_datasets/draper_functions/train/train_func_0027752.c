UninstallReadCbk()
{
    if (pfnReadCbk == NULL)
        return FALSE;

    pfnReadCbk = NULL;
    pReadCbkUserData = NULL;
    bStopOnInterrruptUntilUninstall = FALSE;
    bInterrupted = FALSE;
    return TRUE;
}
