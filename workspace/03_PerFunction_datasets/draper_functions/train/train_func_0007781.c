PR_RmDir(const char *name)
{
    PRInt32 rv;

    if (pt_TestAbort()) return PR_FAILURE;

    rv = rmdir(name);
    if (0 == rv) {
    return PR_SUCCESS;
    } else {
    pt_MapError(_PR_MD_MAP_RMDIR_ERROR, errno);
    return PR_FAILURE;
    }
}
