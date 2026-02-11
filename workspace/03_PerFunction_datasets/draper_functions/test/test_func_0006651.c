shorten_name(name)
    char *name;
{
    int len;
    char *trunc = NULL;
    int plen;
    int min_part = MIN_PART;
    char *p;

    len = strlen(name);
    if (decompress) {
        if (len <= 1)
          gzip_error ("name too short");
        name[len-1] = '\0';
        return;
    }
    p = get_suffix(name);
    if (! p)
      gzip_error ("can't recover suffix\n");
    *p = '\0';
    save_orig_name = 1;


    if (len > 4 && strequ(p-4, ".tar")) {
        strcpy(p-4, ".tgz");
        return;
    }


    do {
        p = strrchr(name, PATH_SEP);
        p = p ? p+1 : name;
        while (*p) {
            plen = strcspn(p, PART_SEP);
            p += plen;
            if (plen > min_part) trunc = p-1;
            if (*p) p++;
        }
    } while (trunc == NULL && --min_part != 0);

    if (trunc != NULL) {
        do {
            trunc[0] = trunc[1];
        } while (*trunc++);
        trunc--;
    } else {
        trunc = strrchr(name, PART_SEP[0]);
        if (!trunc)
          gzip_error ("internal error in shorten_name");
        if (trunc[1] == '\0') trunc--;
    }
    strcpy(trunc, z_suffix);
}
