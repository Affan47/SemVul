fdb_download(int checkhost)
{
    int karma, i, len;
    uint32_t * fdb;
    char * filename, * p;
    char ourhostname[255], hostname[255], path[PATH_MAX];

    currentKarma(0, &karma);
    fdb=lk_properties_andOrSearch(EXACT|ORS, NULL, "path", "");
    if (!fdb)
        return;

    if (checkhost) {
        if (gethostname(ourhostname, 255) != 0) ourhostname[0] = '\0';
        len = strlen(ourhostname) + 1;
    }

    for (i=0; fdb[i]; i++) {
        filename=lk_properties_get_property(fdb[i], "path");
        if (!filename)
            continue;
        memcpy(hostname, filename, 255);
        for (p=hostname; *p != '\0'; p++)
            if (*p == ':')
                break;
        *p = '\0';
        if (checkhost && memcmp(hostname, ourhostname, len) != 0)
            continue;
        memcpy(path, p+1, PATH_MAX);
        printf("Downloading fid %i to %s\n", fdb[i], path);
        fprintf(stderr, "lk_rio_read %s\n",
        CHECK(lk_rio_read(karma, fdb[i], path)));
    }
    free(fdb);
}
