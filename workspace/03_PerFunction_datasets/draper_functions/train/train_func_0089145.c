knowledge_god_summary(const char *item, StringBuffer *buf) {
    char *dup = strdup_local(item), *pos = strchr(dup, ':');

    if (pos)
        *pos = '\0';

    stringbuffer_append_printf(buf, "%s [god]", dup);
    free(dup);
}
