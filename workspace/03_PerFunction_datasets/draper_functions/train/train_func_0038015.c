enter_fixed_template_map(object *pl, object *exit_ob) {
    mapstruct *new_map;
    char tmpnum[32], exitpath[HUGE_BUF], resultname[HUGE_BUF], tmpstring[HUGE_BUF], *sourcemap;
    char new_map_name[MAX_BUF];


    snprintf(exitpath, sizeof(exitpath), "%s", EXIT_PATH(exit_ob)+2);
    sourcemap = strchr(exitpath, '!');
    if (!sourcemap) {
        draw_ext_info_format(NDI_UNIQUE, 0, pl,
                             MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_FAILURE,
                             "The %s is closed.",
                             exit_ob->name);


        LOG(llevError, "enter_fixed_template_map: Exit %s (%d,%d) on map %s has no source template.\n", exit_ob->name, exit_ob->x, exit_ob->y, exit_ob->map->path);
        return;
    }
    *sourcemap++ = '\0';


    if (!exit_ob->map->is_template) {

        path_combine_and_normalize(exit_ob->map->path, sourcemap, tmpstring, sizeof(tmpstring));
        snprintf(exitpath, sizeof(exitpath), "%s", tmpstring);
        sourcemap = exitpath;
    }


    snprintf(tmpnum, sizeof(tmpnum), "%d", exit_ob->x);
    replace(exitpath, "%x", tmpnum, resultname,  sizeof(resultname));

    snprintf(tmpnum, sizeof(tmpnum), "%d", exit_ob->y);
    snprintf(tmpstring, sizeof(tmpstring), "%s", resultname);
    replace(tmpstring, "%y", tmpnum, resultname,  sizeof(resultname));

    snprintf(tmpstring, sizeof(tmpstring), "%s", resultname);
    replace(tmpstring, "%n", exit_ob->map->name, resultname,  sizeof(resultname));


    if (exit_ob->map->is_template && (resultname[0] != '/')) {
        path_combine_and_normalize(exit_ob->map->path, resultname, new_map_name, sizeof(new_map_name));
    } else {
        create_template_pathname(resultname, new_map_name, sizeof(new_map_name));
    }


    new_map = ready_map_name(new_map_name, MAP_PLAYER_UNIQUE);
    if (!new_map) {
        char path[MAX_BUF];

        create_pathname(sourcemap, path, MAX_BUF);
        new_map = load_original_map(path, MAP_PLAYER_UNIQUE);
    }

    if (new_map) {


        snprintf(new_map->path, sizeof(new_map->path), "%s", new_map_name);
        new_map->is_template = 1;
        enter_map(pl, new_map, EXIT_X(exit_ob), EXIT_Y(exit_ob));
    } else {
        draw_ext_info_format(NDI_UNIQUE, 0, pl,
                             MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_FAILURE,
                             "The %s is closed.",
                             exit_ob->name);


        LOG(llevDebug, "enter_fixed_template_map: Exit %s (%d,%d) on map %s leads no where.\n", exit_ob->name, exit_ob->x, exit_ob->y, exit_ob->map->path);
    }
}
