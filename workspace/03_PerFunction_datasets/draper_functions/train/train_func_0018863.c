command_banish(object *op, const char *params) {
    player *pl;
    FILE *banishfile;
    char buf[MAX_BUF];
    time_t now;

    if (*params == '\0') {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                      "Usage: banish <player>.");
        return;
    }

    pl = get_other_player_from_name(op, params);
    if (!pl)
        return;

    snprintf(buf, sizeof(buf), "%s/%s", settings.localdir, BANISHFILE);

    if ((banishfile = fopen(buf, "a")) == NULL) {
        LOG(llevDebug, "Could not find file banish_file.\n");
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                      "Could not find banish_file.");
        return;
    }

    now = time(NULL);


    fprintf(banishfile, "# %s (%s) banned by %s at %s\n", pl->ob->name, pl->socket.host, op->name, ctime(&now));
    fprintf(banishfile, "*@%s\n", pl->socket.host);
    fclose(banishfile);

    LOG(llevDebug, "! %s banned %s from IP: %s.\n", op->name, pl->ob->name, pl->socket.host);

    draw_ext_info_format(NDI_UNIQUE|NDI_RED, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_DM,
                         "You banish %s",
                         pl->ob->name);

    draw_ext_info_format(NDI_UNIQUE|NDI_ALL|NDI_RED, 5, op, MSG_TYPE_ADMIN, MSG_TYPE_ADMIN_DM,
                         "%s banishes %s from the land!",
                         op->name, pl->ob->name);
    command_kick2(op, pl->ob->name);
}
