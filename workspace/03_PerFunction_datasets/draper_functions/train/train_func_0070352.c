ef_cb_efreet_data_dirs(void)
{
    Eina_List *tmp, *l;
    int ret = 1;
    unsigned int i;
    unsigned int ok;
    char dirs[128], *val;
    char *vals[] = {"/var/tmp/a", "/tmp/b", "/usr/local/share", "/etc", NULL};
    char *def_vals[] = {PACKAGE_DATA_DIR, "/usr/share", "/usr/local/share", NULL};

    dirs[0] = '\0';
    for (i = 0; vals[i]; i++)
    {
        if (i > 0) strcat(dirs, ":");
        strcat(dirs, vals[i]);
    }

    efreet_shutdown();
    setenv("XDG_DATA_DIRS", dirs, 1);
    efreet_init();

    ok = 0;
    tmp = efreet_data_dirs_get();
    for (i = 0; vals[i]; i++)
    {
        char *found;

        found = eina_list_search_unsorted(tmp, EINA_COMPARE_CB(strcmp), vals[i]);
        if (!ecore_file_exists(vals[i]) && found)
        {
            printf("efreet_data_dirs_get() includes non-existing dir (%s) when "
                   "%s set\n", vals[i], dirs);
            ret = 0;
            continue;
        }
        if (ecore_file_exists(vals[i]) && !found)
        {
            printf("efreet_data_dirs_get() is missing dir (%s) when "
                   "%s set\n", vals[i], dirs);
            ret = 0;
            continue;
        }
        if (ecore_file_exists(vals[i]) && found)
            ok++;
    }
    if (eina_list_count(tmp) != ok)
    {
        printf("efreet_data_dirs_get() returned more values then it "
               "should have given %s as input\n", dirs);
        ret = 0;
    }

    efreet_shutdown();
    unsetenv("XDG_DATA_DIRS");
    efreet_init();

    i = 0;
    tmp = efreet_data_dirs_get();
    if (eina_list_count(tmp) != 3)
    {
        printf("efreet_data_dirs_get() nodes is differnet from expected default\n");
        ret = 0;
    }

    EINA_LIST_FOREACH(tmp, l, val)
    {
        if (!def_vals[i])
        {
            printf("efreet_data_dirs_get() returned more values then it "
                    "should have given %s as input\n", dirs);
            ret = 0;
            break;
        }

        if (strcmp(val, def_vals[i]))
        {
            printf("efreet_data_dirs_get() returned incorrect value (%s) when "
                    "XDG_DATA_DIRS= is set %s\n", val, def_vals[i]);
            ret = 0;
        }

        i++;
    }
    return ret;
}
