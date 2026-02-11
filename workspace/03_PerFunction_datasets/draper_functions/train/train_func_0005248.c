print_actions(PFormat pf)
{
    char **pentry;
    char format[64];

    sprintf(format, "%%s (%%-%ds): %%s\n", pf->max.action.username);
    for_each_entry(pf, pentry) {
        printf(format, format_date(ACTION(created_at)), ACTION(username), ACTION(message));
    }
}
