getusername(void)
{
#ifdef _WIN32
    static char buf[1024];
    DWORD size = sizeof(buf);
    buf[0] = '\0';
    GetUserName( buf, &size);
    return buf;
#else
    struct passwd *pw = getpwuid(getuid());
    if ( pw == NULL )
        fatal("getpwuid() failed for uid: %d\n", getuid());
    return pw->pw_name;
#endif
}
