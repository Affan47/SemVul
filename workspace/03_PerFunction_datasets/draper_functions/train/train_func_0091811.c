add_group(Cfg *cfg, CfgGroup *grp)
{
    Octstr *groupname;
    Octstr *name;
    List *names;
    List *list;

    groupname = cfg_get(grp, octstr_imm("group"));
    if (groupname == NULL) {
        error(0, "Group does not contain variable 'group'.");
        return -1;
    }
    set_group_name(grp, groupname);

    names = dict_keys(grp->vars);

    while ((name = gwlist_extract_first(names)) != NULL) {
        int a = is_allowed_in_group(groupname, name);
        switch (a) {
            case 0:
                error(0, "Group '%s' may not contain field '%s'.",
                      octstr_get_cstr(groupname), octstr_get_cstr(name));
                octstr_destroy(name);
                octstr_destroy(groupname);
                gwlist_destroy(names, octstr_destroy_item);
                return -1;
                break;
            case -1:
                error(0, "Group '%s' is no valid group identifier.",
                      octstr_get_cstr(groupname));
                octstr_destroy(name);
                octstr_destroy(groupname);
                gwlist_destroy(names, octstr_destroy_item);
                return -1;
                break;
            default:
                octstr_destroy(name);
                break;
        }
    }
    gwlist_destroy(names, NULL);

    if (is_single_group(groupname)) {
        dict_put(cfg->single_groups, groupname, grp);
    } else {
        list = dict_get(cfg->multi_groups, groupname);
        if (list == NULL) {
            list = gwlist_create();
            dict_put(cfg->multi_groups, groupname, list);
        }
        gwlist_append(list, grp);
    }

    octstr_destroy(groupname);
    return 0;
}
