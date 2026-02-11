certificate_verify_callback(int preverify_ok, X509_STORE_CTX * ctx) {
    char fnm[FILE_PATH_SIZE];
    DIR * dir = NULL;
    int err = 0;
    int found = 0;

    snprintf(fnm, sizeof(fnm), "%s/ssl", tcf_dir);
    if (!err && (dir = opendir(fnm)) == NULL) err = errno;
    while (!err && !found) {
        int l = 0;
        X509 * cert = NULL;
        FILE * fp = NULL;
        struct dirent * ent = readdir(dir);
        if (ent == NULL) break;
        l = strlen(ent->d_name);
        if (l < 5 || strcmp(ent->d_name + l -5 , ".cert") != 0) continue;
        snprintf(fnm, sizeof(fnm), "%s/ssl/%s", tcf_dir, ent->d_name);
        if (!err && (fp = fopen(fnm, "r")) == NULL) err = errno;
        if (!err && (cert = PEM_read_X509(fp, NULL, NULL, NULL)) == NULL) err = ERR_SSL;
        if (!err && fclose(fp) != 0) err = errno;
        if (!err && X509_cmp(X509_STORE_CTX_get_current_cert(ctx), cert) == 0) found = 1;
    }
    if (dir != NULL && closedir(dir) < 0 && !err) err = errno;
    if (err) trace(LOG_ALWAYS, "Cannot read certificate: %s",
        err == ERR_SSL ? ERR_error_string(ERR_get_error(), NULL) : errno_to_str(err));
    return err == 0 && found;
}
