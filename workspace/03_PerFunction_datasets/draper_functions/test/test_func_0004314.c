httpReadGroupFile(HttpAuth *auth, char *path)
{
    MprFile     *file;
    HttpAcl     acl;
    char        *buf;
    char        *users, *group, *enabled, *aclSpec, *tok, *cp;

    auth->groupFile = sclone(path);

    if ((file = mprOpenFile(path, O_RDONLY | O_TEXT, 0444)) == 0) {
        return MPR_ERR_CANT_OPEN;
    }
    while ((buf = mprReadLine(file, MPR_BUFSIZE, NULL)) != NULL) {
        enabled = stok(buf, " :\t", &tok);
        for (cp = enabled; cp && isspace((int) *cp); cp++) { }
        if (cp == 0 || *cp == '\0' || *cp == '#') {
            continue;
        }
        aclSpec = stok(NULL, " :\t", &tok);
        group = stok(NULL, " :\t", &tok);
        users = stok(NULL, "\r\n", &tok);

        acl = httpParseAcl(auth, aclSpec);
        httpAddGroup(auth, group, acl, (*enabled == '0') ? 0 : 1);
        httpAddUsersToGroup(auth, group, users);
    }
    httpUpdateUserAcls(auth);
    mprCloseFile(file);
    return 0;
}
