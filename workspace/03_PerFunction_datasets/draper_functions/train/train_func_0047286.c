rmkdir(char *path)
{


    char *i = strrchr(path, '/');

    if(path[0] == '\0'  ||  dir_exists(path))
        return 0;

    if (i != NULL)
    {
        *i = '\0';
        rmkdir(path);
        *i = '/';
        mkdir(path, 0777);
    }

#ifdef WIN32
        return 0;
#else
    if (dir_exists(path))
        return 0;
    else
        return -1;
#endif
}
