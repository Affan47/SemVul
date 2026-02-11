enter_player_savebed(object *op) {
    mapstruct *oldmap = op->map;
    object *tmp;

    tmp = object_new();

    EXIT_PATH(tmp) = add_string(op->contr->savebed_map);
    EXIT_X(tmp) = op->contr->bed_x;
    EXIT_Y(tmp) = op->contr->bed_y;
    enter_exit(op, tmp);


    if (oldmap == op->map && strcmp(op->contr->savebed_map, oldmap->path)) {
        LOG(llevDebug, "Player %s savebed location %s is invalid - going to emergency location (%s)\n", settings.emergency_mapname, op->name, op->contr->savebed_map);
        strcpy(op->contr->savebed_map, settings.emergency_mapname);
        op->contr->bed_x = settings.emergency_x;
        op->contr->bed_y = settings.emergency_y;
        free_string(op->contr->savebed_map);
        EXIT_PATH(tmp) = add_string(op->contr->savebed_map);
        EXIT_X(tmp) = op->contr->bed_x;
        EXIT_Y(tmp) = op->contr->bed_y;
        enter_exit(op, tmp);
    }
    object_free2(tmp, FREE_OBJ_NO_DESTROY_CALLBACK);
}
