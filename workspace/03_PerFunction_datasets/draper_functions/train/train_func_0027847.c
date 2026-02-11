process_action_line(const gchar * line)
{
    static gchar *action_name = NULL;
    const gchar *str = line;
    gint length;
    gboolean is_action_name;

    if (*line == '\n' || *line == '\0' || *line == '#')

        return;

    if (g_str_has_prefix(line, "action_name") == FALSE &&
        g_str_has_prefix(line, "action_command") == FALSE)
        return;

    is_action_name = g_str_has_prefix(line, "action_name");
    str += is_action_name ? strlen("action_name") : strlen("action_command");
    while (*str == ' ' || *str == '\t')
        str++;

    if (*str != '=')

        return;

    do {
        str++;
    } while (*str == ' ' || *str == '\t');

    length = strlen(str);
    while (length > 0 && str[length - 1] == '\n')
        length--;

    if (is_action_name) {
        g_free(action_name);
        action_name = g_strndup(str, length);

    } else if (action_name != NULL) {
        gchar *action_command = g_strndup(str, length);

        add_action(action_name, action_command);
        g_free(action_name);
        g_free(action_command);
        action_name = NULL;
    }
}
