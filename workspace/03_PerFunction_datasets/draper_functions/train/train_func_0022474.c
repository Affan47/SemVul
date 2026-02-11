saveAuthorizations(struct display *d, char **authFile, Xauth **auths, int count)
{
    FILE *auth_file;
    int i;

    if (*authFile) {
        if (!(auth_file = fdOpenW(creat(*authFile, 0600)))) {
            logError("Cannot open X server authorization file %s\n", *authFile);
            free(*authFile);
            *authFile = 0;
            return False;
        }
    } else {
        if (!(auth_file = makeServerAuthFile(d, authFile))) {
            logError("Cannot create X server authorization file\n");
            return False;
        }
    }
    debug("file: %s  auth: %p\n", *authFile, auths);
    for (i = 0; i < count; i++) {


        if (auths[i]->data_length > 0)
            if (!XauWriteAuth(auth_file, auths[i])) {
                fclose(auth_file);
                goto whoops;
            }
    }
    if (fclose(auth_file) == EOF) {
      whoops:
        logError("Cannot write X server authorization file %s: %m\n",
                 *authFile);
        unlink(*authFile);
        free(*authFile);
        *authFile = 0;
        return False;
    }
    return True;
}
