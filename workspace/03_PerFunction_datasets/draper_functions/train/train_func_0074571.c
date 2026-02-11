add_match(Match_Type type, const char *ptn)
{
    Match *m = malloc(sizeof(Match));
    m->regex = ptn;
    m->type = type;
    int rtn = regcomp(&m->preg, ptn,
      REG_EXTENDED | REG_ICASE | REG_NOSUB | REG_NEWLINE);
    if (rtn != 0) {
        size_t buf_size = regerror(rtn, &m->preg, NULL, 0);
        char *buf = malloc(buf_size);
        if (buf == NULL)
            errx(1, "Out of memory");
        regerror(rtn, &m->preg, buf, buf_size);
        warnx("Error when compiling regular expression '%s': %s", ptn, buf);
        free(buf);
        return NULL;
    }

    m->next = NULL;

    return m;
}
