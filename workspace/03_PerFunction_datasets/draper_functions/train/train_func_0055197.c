efreet_mime_shared_mimeinfo_globs_load(const char *file)
{
    FILE *f = NULL;
    char buf[4096], mimetype[4096], ext[4096], *p, *pp;
    Efreet_Mime_Glob *mime = NULL;

    f = fopen(file, "rb");
    if (!f) return;

    while (fgets(buf, sizeof(buf), f))
    {
        p = buf;
        while (isspace(*p) && (*p != 0) && (*p != '\n')) p++;

        if (*p == '#') continue;
        if ((*p == '\n') || (*p == 0)) continue;

        pp = p;
        while ((*p != ':') && (*p != 0) && (*p != '\n')) p++;

        if ((*p == '\n') || (*p == 0)) continue;
        strncpy(mimetype, pp, (p - pp));
        mimetype[p - pp] = 0;
        p++;
        pp = ext;

        while ((*p != 0) && (*p != '\n'))
        {
            *pp = *p;
            pp++;
            p++;
        }

        *pp = 0;

        if (ext[0] == '*' && ext[1] == '.')
        {
            eina_hash_del(wild, &(ext[2]), NULL);
            eina_hash_add(wild, &(ext[2]),
                            (void*)eina_stringshare_add(mimetype));
        }
        else
        {
            mime = NEW(Efreet_Mime_Glob, 1);
            if (mime)
            {
                mime->mime = eina_stringshare_add(mimetype);
                mime->glob = eina_stringshare_add(ext);
                if ((!mime->mime) || (!mime->glob))
                {
                    IF_RELEASE(mime->mime);
                    IF_RELEASE(mime->glob);
                    FREE(mime);
                }
                else
                {
                    efreet_mime_glob_remove(ext);
                    globs = eina_list_append(globs, mime);
                }
            }
        }
    }

    fclose(f);
}
