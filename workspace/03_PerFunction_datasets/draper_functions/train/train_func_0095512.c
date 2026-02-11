PR_DeleteSemaphore(const char *name)
{
    key_t key;
    int semid;

    union semun unused;
    char osname[PR_IPC_NAME_SIZE];

    if (_PR_MakeNativeIPCName(name, osname, sizeof(osname), _PRIPCSem)
        == PR_FAILURE)
    {
        return PR_FAILURE;
    }
    key = ftok(osname, NSPR_IPC_KEY_ID);
    if ((key_t) -1 == key)
    {
        _PR_MD_MAP_DEFAULT_ERROR(errno);
        return PR_FAILURE;
    }
    if (unlink(osname) == -1)
    {
        _PR_MD_MAP_UNLINK_ERROR(errno);
        return PR_FAILURE;
    }
    semid = semget(key, 1, NSPR_SEM_MODE);
    if (-1 == semid)
    {
        _PR_MD_MAP_DEFAULT_ERROR(errno);
        return PR_FAILURE;
    }
    unused.val = 0;
    if (semctl(semid, 0, IPC_RMID, unused) == -1)
    {
        _PR_MD_MAP_DEFAULT_ERROR(errno);
        return PR_FAILURE;
    }
    return PR_SUCCESS;
}
