PR_CloseDir(PRDir *dir)
{
    if (pt_TestAbort()) return PR_FAILURE;

    if (NULL != dir->md.d)
    {
        if (closedir(dir->md.d) == -1)
        {
            _PR_MD_MAP_CLOSEDIR_ERROR(errno);
            return PR_FAILURE;
        }
        dir->md.d = NULL;
        PR_DELETE(dir);
    }
    return PR_SUCCESS;
}
