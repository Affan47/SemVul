GetFullFilePath(const char* oldPath)
{
    char path[2048];

    ASSERT(oldPath);

    if (oldPath[0] == '\0')
    {
        (void)getcwd(path, 1024);
    }
    else if (oldPath[0] == '.')
    {
        (void)getcwd(path, 1024);
        (void)strcat(path, "/");
        (void)strcat(path, oldPath);
    }
    else if (oldPath[0] == '~')
    {
#ifdef DXD_OS_NON_UNIX
        printf("Can't use ~ when running ui on NT or Windows\n");
#else
        char* home;

        if (oldPath[1] == '/' || oldPath[1] == '\0')
        {
            home = getenv("HOME");
            if (home == NULL)
            {
                strcpy(path, oldPath);
            }
            else
            {
                strcpy(path, home);
                strcat(path, oldPath + 1);
            }
        }
        else
        {
            char user[1024];
            struct passwd *ent;
            int i;


            for (i = 1; oldPath[i] && oldPath[i] != '/'; ++i)
            {
                user[i - 1] = oldPath[i];
            }
            user[i -1] = '\0';
            ent = getpwnam(user);

            if (ent == NULL)
            {
                strcpy(path, oldPath);
            }
            else
            {
                strcpy(path, ent->pw_dir);
                strcat(path, oldPath + i);
            }
        }
#endif
    }
#ifndef DXD_NON_UNIX_DIR_SEPARATOR
    else if (oldPath[0] != '/')
#else

    else if (!( (oldPath[0] == '/') || (oldPath[0] == '\\') ||
		((oldPath[1] == ':')&&(isalpha(oldPath[0]))) ))
#endif
    {
        getcwd(path, 1024);
        strcat(path, "/");
        strcat(path, oldPath);
    }
    else
    {
        strcpy(path, oldPath);
    }

    return FilterDottedPath(path);
}
