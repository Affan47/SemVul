parse_lookup(const char *p, const struct rule *rule, int *value)
{
    size_t i;

    for (i = 0; i < rule->size; i++)
        if (strncasecmp(rule->table[i], p, rule->max) == 0) {
            p += rule->max;
            *value = i;
            return p;
        }
    return NULL;
}
