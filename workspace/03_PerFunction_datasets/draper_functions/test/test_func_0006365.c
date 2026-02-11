cut_utils_inspect_string_to_gstring (GString *inspected, const gchar *string)
{
    if (!string) {
        g_string_append(inspected, "(null)");
        return;
    }

    g_string_append_c(inspected, '"');
    for (; string[0]; string++) {
        switch (string[0]) {
        case '"':
            g_string_append(inspected, "\\\"");
            break;
        case '\\':
            g_string_append(inspected, "\\\\");
            break;
        default:
            g_string_append_c(inspected, string[0]);
            break;
        }
    }
    g_string_append_c(inspected, '"');
}
