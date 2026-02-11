xkb_find_flag_from_name(xkbGroup *group) {
    int i;

    group->flag_xpm = NULL;


    if (! group->name) {
        group->flag_xpm = flag_xpm_unknown;
        return;
    }

    i = 0;
    while (global_names_map[i].country_name) {
        if (STARTS_WITH(group->name, global_names_map[i].country_name)) {
            group->flag_xpm = global_names_map[i].flag_pointer;
            return;
        }
        i++;
    }

    if (group->flag_xpm == NULL) group->flag_xpm = flag_xpm_unknown;

    return;
}
