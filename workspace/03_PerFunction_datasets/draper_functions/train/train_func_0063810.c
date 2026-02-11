hfile_oflags(const char *mode)
{
    int rdwr = 0, flags = 0;
    const char *s;
    for (s = mode; *s; s++)
        switch (*s) {
        case 'r': rdwr = O_RDONLY;  break;
        case 'w': rdwr = O_WRONLY; flags |= O_CREAT | O_TRUNC;  break;
        case 'a': rdwr = O_WRONLY; flags |= O_CREAT | O_APPEND;  break;
        case '+': rdwr = O_RDWR;  break;
        default:  break;
        }

#ifdef O_BINARY
    flags |= O_BINARY;
#endif

    return rdwr | flags;
}
