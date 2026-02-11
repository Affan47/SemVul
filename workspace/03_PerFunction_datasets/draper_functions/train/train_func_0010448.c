P_Open(int argc, Object *argv) {
    Object fn;
    int mode, n;

    fn = argv[0];
    mode = (int)Symbols_To_Bits(argv[1], 1, Open_Syms);
    if (!(n = mode & 3))
        Primitive_Error("mode must include 'read or 'write");
    mode &= ~3; mode |= n-1;
    if (mode & O_CREAT && argc == 2)
        Primitive_Error("third argument required for 'create");
    if ((n = open(Get_Strsym(fn), mode, argc == 3 ? Get_Integer(argv[2]) : 0))
            == -1)
        Raise_System_Error1("~s: ~E", fn);
    return Make_Integer(n);
}
