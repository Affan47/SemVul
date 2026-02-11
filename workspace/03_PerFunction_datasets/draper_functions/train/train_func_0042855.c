plugins_display_list(object *op) {
    crossfire_plugin *cp;

    draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_DEBUG,
                  "List of loaded plugins:\n-----------------------");

    if (plugins_list == NULL)
        return;

    for (cp = plugins_list; cp != NULL; cp = cp->next) {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_DEBUG,
                             "%s, %s",
                             cp->id, cp->fullname);
    }
}
