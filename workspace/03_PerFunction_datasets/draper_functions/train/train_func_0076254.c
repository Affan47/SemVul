P_Filedescriptor_Flags(int argc, Object *argv) {
    int flags = 0, fd;

    fd = Get_Integer(argv[0]);
#ifndef WIN32
    if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
        Raise_System_Error("fcntl(F_GETFL): ~E");
#endif
    if (argc == 2) {
#ifndef WIN32
        if (fcntl(fd, F_SETFL, Symbols_To_Bits(argv[1], 1, Fcntl_Flags)) == -1)
            Raise_System_Error("fcntl(F_SETFL): ~E");
#endif
    }
    return Bits_To_Symbols((unsigned long)flags, 1, Fcntl_Flags);
}
