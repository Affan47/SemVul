PR_CreatePipe(
    PRFileDesc **readPipe,
    PRFileDesc **writePipe
)
{
    int pipefd[2];

    if (pt_TestAbort()) return PR_FAILURE;

    if (pipe(pipefd) == -1)
    {

        PR_SetError(PR_UNKNOWN_ERROR, errno);
        return PR_FAILURE;
    }
    *readPipe = pt_SetMethods(pipefd[0], PR_DESC_PIPE, PR_FALSE, PR_FALSE);
    if (NULL == *readPipe)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return PR_FAILURE;
    }
    *writePipe = pt_SetMethods(pipefd[1], PR_DESC_PIPE, PR_FALSE, PR_FALSE);
    if (NULL == *writePipe)
    {
        PR_Close(*readPipe);
        close(pipefd[1]);
        return PR_FAILURE;
    }
    return PR_SUCCESS;
}
