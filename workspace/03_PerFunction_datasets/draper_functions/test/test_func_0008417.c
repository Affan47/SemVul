parse_host_line(const char *line, int max, GListPtr * output)
{
    int lpc = 0;
    int last = 0;

    if (max <= 0) {
        return;
    }


    if (strstr(line, "invalid") || strstr(line, "variable")) {
        crm_debug("Skipping: %s", line);
        return;
    }

    crm_trace("Processing %d bytes: [%s]", max, line);

    for (lpc = 0; lpc <= max && isspace(line[lpc]); lpc++) {
        last = lpc + 1;
    }


    for (lpc = 0; lpc <= max; lpc++) {
        gboolean a_space = isspace(line[lpc]);

        if (a_space && lpc < max && isspace(line[lpc + 1])) {


        } else if (a_space || line[lpc] == ',' || line[lpc] == 0) {
            int rc = 1;
            char *entry = NULL;

            if (lpc != last) {
                entry = calloc(1, 1 + lpc - last);
                rc = sscanf(line + last, "%[a-zA-Z0-9_-.]", entry);
            }

            if (entry == NULL) {

            } else if (rc != 1) {
                crm_warn("Could not parse (%d %d): %s", last, lpc, line + last);
            } else if (safe_str_neq(entry, "on") && safe_str_neq(entry, "off")) {
                crm_trace("Adding '%s'", entry);
                *output = g_list_append(*output, entry);
                entry = NULL;
            }

            free(entry);
            last = lpc + 1;
        }
    }
}
