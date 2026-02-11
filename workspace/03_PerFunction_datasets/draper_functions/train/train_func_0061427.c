mt_match(char *buf, mem_type_t *m)
{
    gulong val;
    int len;

    len = strlen(m->name);
    if (strncmp(buf, m->name, len))
        return FALSE;
    if (sscanf(buf + len + 1, "%lu", &val) != 1)
        return FALSE;
    m->val = val;
    m->valid = 1;
    DBG("%s: %lu\n", m->name, val);
    return TRUE;
}
