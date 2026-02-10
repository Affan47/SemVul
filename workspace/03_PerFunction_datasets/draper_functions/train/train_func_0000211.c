P_Lseek(Object fd, Object off, Object whence) {
    off_t ret;

    if ((ret = lseek(Get_Integer(fd), (off_t)Get_Long(off),
            (int)Symbols_To_Bits(whence, 0, Lseek_Syms))) == (off_t)-1)
        Raise_System_Error("~E");
    return Make_Unsigned_Long((unsigned long)ret);
}
