PR_Stat(const char *name, struct stat *buf)
{
    static PRBool unwarned = PR_TRUE;
    if (unwarned) unwarned = _PR_Obsolete("PR_Stat", "PR_GetFileInfo");

    if (pt_TestAbort()) return -1;

    if (-1 == stat(name, buf)) {
        pt_MapError(_PR_MD_MAP_STAT_ERROR, errno);
        return -1;
    } else {
        return 0;
    }
}
