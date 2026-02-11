waitForGdbInput(void)
{
    int numfds;
    fd_set readfds;

    FD_ZERO (&readfds);
    FD_SET (gdbFileDescriptor, &readfds);

    numfds = select (gdbFileDescriptor + 1, &readfds, 0, 0, 0);
    gdbCheck(numfds);
}
