command_wimpy(object *op, const char *params) {
    int i;

    if (*params == '\0' || !sscanf(params, "%d", &i)) {
        draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_CONFIG,
                             i18n(op, "Your current wimpy level is %d."),
                             op->run_away);
        return;
    }

    draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_CONFIG,
                         i18n(op, "Your new wimpy level is %d."),
                         i);
    op->run_away = i;
}
