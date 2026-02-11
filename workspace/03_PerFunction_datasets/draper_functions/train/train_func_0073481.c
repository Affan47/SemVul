get_who_escape_code_value(char *return_val, int size, const char letter, player *pl) {
    switch (letter) {
    case 'N':
        snprintf(return_val, size, "%s", pl->ob->name);
        break;

    case 't':
        player_get_title(pl, return_val, size);
        break;

    case 'c':
        snprintf(return_val, size, "%u", pl->ob->count);
        break;

    case 'n':
        snprintf(return_val, size, "\n");
        break;

    case 'h':
        snprintf(return_val, size, "%s", pl->peaceful ? "" : " <Hostile>");
        break;

    case 'l':
        snprintf(return_val, size, "%d", pl->ob->level);
        break;

    case 'd':
        snprintf(return_val, size, "%s", (QUERY_FLAG(pl->ob, FLAG_WIZ) ? " <WIZ>" : ""));
        break;

    case 'a':
        snprintf(return_val, size, "%s", (QUERY_FLAG(pl->ob, FLAG_AFK) ? " <AFK>" : ""));
        break;

    case 'b':
        snprintf(return_val, size, "%s", (pl->socket.is_bot == 1) ? " <BOT>" : "");
        break;

    case 'm':
        snprintf(return_val, size, "%s", pl->ob->map->path);
        break;

    case 'M':
        snprintf(return_val, size, "%s", pl->ob->map->name ? pl->ob->map->name : "Untitled");
        break;

    case 'r':
        snprintf(return_val, size, "%s", get_name_of_region_for_map(pl->ob->map));
            break;

    case 'R':
        snprintf(return_val, size, "%s", get_region_longname(get_region_by_map(pl->ob->map)));
        break;

    case 'i':
        snprintf(return_val, size, "%s", pl->socket.host);
        break;

    case '%':
        snprintf(return_val, size, "%%");
        break;

    case '_':
        snprintf(return_val, size, "_");
        break;
    }
}
