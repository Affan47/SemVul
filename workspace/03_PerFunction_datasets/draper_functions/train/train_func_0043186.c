FilterDottedPath(const char* oldPath)
{
    char* path;
    int   i;
    int   j;

    ASSERT(oldPath);

    path = DuplicateString(oldPath);

    DOS2UNIXPATH(path);

    i = j = 0;
    while(TRUE)
    {
        if (path[j] == '.')
        {
            j++;
            if (path[j] == '.')
            {
                j++;
                if (path[j] == '/')
                {
                    for(i--; path[i] != '/'; i--)
                        ;

                    if (i > 0)
                    {
                        for(i--; path[i] != '/'; i--)
                            ;
                    }
                }
                else if (path[j] == '\0')
                {
                    for(i--; path[i] != '/'; i--)
                        ;

                    if (i > 0)
                    {
                        for(i--; path[i] != '/'; i--)
                            ;
                    }

                    if (i == 0)
                    {
                        i++;
                    }
                }
                else
                {
                    j -= 2;
                }
            }
            else if (path[j] == '/')
            {
                j++;
            }
            else if (path[j] == '\0')
            {
                if (i - 1 > 0)
                {
                    i--;
                }
            }
            else
            {
                j--;
            }
        }

        path[i] = path[j];

        if (NOT path[i])
            break;

        i++;
        j++;
    }

    return path;
}
