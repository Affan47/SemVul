dump_map(const mapstruct *m) {
    LOG(llevError, "Map %s status: %d.\n", m->path, m->in_memory);
    LOG(llevError, "Size: %dx%d Start: %d,%d\n", MAP_WIDTH(m), MAP_HEIGHT(m), MAP_ENTER_X(m), MAP_ENTER_Y(m));

    if (m->msg != NULL)
        LOG(llevError, "Message:\n%s", m->msg);

    if (m->maplore != NULL)
        LOG(llevError, "Lore:\n%s", m->maplore);

    if (m->tmpname != NULL)
        LOG(llevError, "Tmpname: %s\n", m->tmpname);

    LOG(llevError, "Difficulty: %d\n", m->difficulty);
    LOG(llevError, "Darkness: %d\n", m->darkness);
}
