load_temporary_map(mapstruct *m) {
    FILE *fp;
    char buf[MAX_BUF];

    if (!m->tmpname) {
        LOG(llevError, "No temporary filename for map %s\n", m->path);
        return 1;
    }

    if ((fp = fopen(m->tmpname, "r")) == NULL) {
        LOG(llevError, "Cannot open %s: %s\n", m->tmpname, strerror_local(errno, buf, sizeof(buf)));
        return 2;
    }

    if (load_map_header(fp, m)) {
        LOG(llevError, "Error loading map header for %s (%s)\n", m->path, m->tmpname);
        return 3;
    }
    allocate_map(m);

    m->in_memory = MAP_LOADING;
    load_objects(m, fp, 0);
    fclose(fp);
    m->in_memory = MAP_IN_MEMORY;
    return 0;
}
