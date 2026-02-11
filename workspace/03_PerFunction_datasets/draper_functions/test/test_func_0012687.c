xml_parse_version(struct playlist* pl, ezxml_t xml, ...)
{
    va_list ap;
    ezxml_t r;

    va_start(ap, xml);
    r = ezxml_vget(xml, ap);
    va_end(ap);

    if (r) {
        char ver[64];
        strncpy(ver, r->txt, sizeof ver);
        ver[sizeof ver-1] = 0;
        int collab;
        if (sscanf(ver, "%u,%u,%u,%u", &pl->revision, &pl->num_tracks,
                    &pl->checksum, &collab) != 4) {
            DSFYDEBUG("!!! List version parsing failed (%s)\n", ver);
        }
        pl->is_collaborative = collab;
    }
}
