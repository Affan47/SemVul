PR_CreateProcessDetached(
    const char *path,
    char *const *argv,
    char *const *envp,
    const PRProcessAttr *attr)
{
    PRProcess *process;
    PRStatus rv;

    process = PR_CreateProcess(path, argv, envp, attr);
    if (NULL == process) {
	return PR_FAILURE;
    }
    rv = PR_DetachProcess(process);
    PR_ASSERT(PR_SUCCESS == rv);
    if (rv == PR_FAILURE) {
	PR_DELETE(process);
	return PR_FAILURE;
    }
    return PR_SUCCESS;
}
