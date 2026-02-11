xmlParseURIPathSegments(xmlURIPtr uri, const char **str, int slash)
{
    const char *cur;

    if (str == NULL)
        return (-1);

    cur = *str;

    do {
        while ((IS_PCHAR(cur)) ||
               ((uri != NULL) && (uri->cleanup & 1) && (IS_UNWISE(cur))))
            NEXT(cur);
        while (*cur == ';') {
            cur++;
            while ((IS_PCHAR(cur)) ||
                   ((uri != NULL) && (uri->cleanup & 1) && (IS_UNWISE(cur))))
                NEXT(cur);
        }
        if (*cur != '/')
            break;
        cur++;
    } while (1);
    if (uri != NULL) {
        int len, len2 = 0;
        char *path;


        len = cur - *str;
        if (slash)
            len++;

        if (uri->path != NULL) {
            len2 = strlen(uri->path);
            len += len2;
        }
        path = (char *) xmlMallocAtomic(len + 1);
        if (path == NULL) {
            xmlGenericError(xmlGenericErrorContext,
                            "xmlParseURIPathSegments: out of memory\n");
            *str = cur;
            return (-1);
        }
        if (uri->path != NULL)
            memcpy(path, uri->path, len2);
        if (slash) {
            path[len2] = '/';
            len2++;
        }
        path[len2] = 0;
        if (cur - *str > 0) {
            if (uri->cleanup & 2) {
                memcpy(&path[len2], *str, cur - *str);
                path[len2 + (cur - *str)] = 0;
            } else
                xmlURIUnescapeString(*str, cur - *str, &path[len2]);
        }
        if (uri->path != NULL)
            xmlFree(uri->path);
        uri->path = path;
    }
    *str = cur;
    return (0);
}
