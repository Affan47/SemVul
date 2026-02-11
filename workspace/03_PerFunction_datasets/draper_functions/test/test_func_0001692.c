P_Append_Set (int argc, Object *argv) {
    register int i, j;

    for (i = j = 0; i < argc; i++)
        if (!Nullp (argv[i]))
            argv[j++] = argv[i];
    if (j == 0)
        return Null;
    for (i = 0; i < j-1; i++)
        (void)P_Set_Cdr (P_Last_Pair (argv[i]), argv[i+1]);
    return *argv;
}
