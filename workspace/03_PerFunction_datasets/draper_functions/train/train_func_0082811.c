P_Pipe() {
    int fd[2];

#ifdef WIN32
    if (_pipe(fd, 256, O_BINARY) == -1)
#else
    if (pipe(fd) == -1)
#endif
        Raise_System_Error("~E");
    return Integer_Pair(fd[0], fd[1]);
}
