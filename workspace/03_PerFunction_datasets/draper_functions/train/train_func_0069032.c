CgiRegister(Mod *modPtr, char *map)
{
    int             ok = 0;
    char           *method;
    char           *url;
    char           *path;
    Ns_DString      ds1, ds2;
    Map            *mapPtr;

    Ns_DStringInit(&ds1);
    Ns_DStringInit(&ds2);

    Ns_DStringAppend(&ds1, map);
    method = ds1.string;
    url = NextWord(method);
    if (*method == '\0' || *url == '\0') {
        Ns_Log(Error, "nscgi: invalid mapping: %s", map);
        goto done;
    }

    path = NextWord(url);
    if (*path == '\0') {
        path = NULL;
    } else {
        Ns_NormalizePath(&ds2, path);
        path = ds2.string;
        if (!Ns_PathIsAbsolute(path) || access(path, R_OK) != 0) {
            Ns_Log(Error, "nscgi: invalid directory: %s", path);
            goto done;
        }
    }
    mapPtr = ns_malloc(sizeof(Map));
    mapPtr->modPtr = modPtr;
    mapPtr->url = ns_strdup(url);
    mapPtr->path = ns_strcopy(path);
    Ns_Log(Notice, "nscgi: %s %s%s%s",
            method, url, path ? " -> " : "", path ? path : "");
    Ns_RegisterRequest(modPtr->server, method, url,
            CgiRequest, CgiFreeMap, mapPtr, 0);
    ok = 1;

done:
    Ns_DStringFree(&ds1);
    Ns_DStringFree(&ds2);
    return ok;
}
