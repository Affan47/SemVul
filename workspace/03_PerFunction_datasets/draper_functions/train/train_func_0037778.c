player_get_title(const struct pl *pl, char *buf, size_t bufsize) {
    if (pl->own_title[0] == '\0')
        snprintf(buf, bufsize, "the %s", pl->title);
    else
        snprintf(buf, bufsize, "%s", pl->own_title);
}
