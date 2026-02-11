Open_File (char *name, int flags, int err) {
    register FILE *f;
    char *dir, *p;
    Object fn, port;
    struct stat st;
    Alloca_Begin;

    p = Internal_Tilde_Expand (name, &dir);
    if (p) {
        Alloca (name, char*, strlen (dir) + 1 + strlen (p) + 1);
        sprintf (name, "%s" SEPARATOR_STRING "%s", dir, p);
    }
    if (!err && stat (name, &st) == -1 &&
            (errno == ENOENT || errno == ENOTDIR)) {
        Alloca_End;
        return Null;
    }
    switch (flags & (P_INPUT|P_BIDIR)) {
    case 0:               p = "w";  break;
    case P_INPUT:         p = "r";  break;
    default:              p = "r+"; break;
    }
    fn = Make_String (name, strlen (name));
    Disable_Interrupts;
    if ((f = fopen (name, p)) == NULL) {
        Saved_Errno = errno;
        Primitive_Error ("~s: ~E", fn);
    }
    port = Make_Port (flags, f, fn);
    Register_Object (port, (GENERIC)0, Terminate_File, 0);
    Enable_Interrupts;
    Alloca_End;
    return port;
}
