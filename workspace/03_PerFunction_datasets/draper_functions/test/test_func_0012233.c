jte_add_path_match(struct libjte_env *o, char *pattern, int flag)
{
    struct path_match *new = NULL, **old;
    int mode;

    mode = flag & 255;
    if (mode == 0)
        old = &(o->include_list);
    else
        old = &(o->exclude_list);

    new = malloc(sizeof *new);
    if (new == NULL)
        return libjte_report_no_mem(o, sizeof *new, 0);

    regcomp(&new->match_pattern, pattern, REG_NEWLINE);
    new->match_rule = strdup(pattern);
    if (new->match_rule == NULL)
        return libjte_report_no_mem(o, sizeof *new, 0);


    new->next = *old;

    *old = new;
    return 0;
}
